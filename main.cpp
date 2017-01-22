#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_eps.hpp>

#include <iostream>
#include <string>
#include <vector>


namespace qi = boost::spirit::qi;

typedef std::vector<uint8_t> coap_payload; 

struct coap_option {
  
  uint16_t number = 0;
  std::vector<uint8_t> values;
};

typedef std::vector<coap_option> coap_options_list; 

struct coap_message {

  uint8_t version;
  uint8_t type;  
                
  uint8_t code_class;
  uint8_t code_detail;

  uint16_t message_id;

  std::vector<uint8_t> token;
  
  coap_options_list options;
  coap_payload payload;
};

template <typename Iterator>
bool coap_message_parser(Iterator first, Iterator last, coap_message &msg)
{
    using qi::byte_;
    using qi::word;
    using qi::hex;
    using qi::eps;
    using boost::phoenix::ref;
    using boost::phoenix::push_back;
    using boost::phoenix::clear;
    using qi::_1;
    using qi::parse;
    using qi::repeat;   

    namespace phnx = boost::phoenix;
 
    uint8_t coap_header = 0;
    uint8_t coap_code = 0;
    uint8_t option_header = 0;
    uint32_t delta = 0;
    uint8_t option_delta_length = 0;

    coap_option option{};   
 
    bool r = parse(first, last, 
             (
              //header version:2-type:2-tag length:4
              byte_[ref(coap_header) = _1]
    
              //code:8
              >> byte_[ref(coap_code) = _1]

              //message id:16
              >> word[ref(msg.message_id) = _1]

              //token:0-8 (here 0-15)
              >> repeat((ref(coap_header) & 0b00001111))[byte_[push_back(phnx::ref(msg.token),_1)]]

              //options
              >> *(
                   //option header:8
                   byte_[ref(option_header) = _1] 
                   >> (
                        ( eps(ref(option_header) == 0xFF) >> +byte_[push_back(phnx::ref(msg.payload),_1)])
                        |
                        (
                        eps(ref(delta) = (ref(option_header) >> 4 )) >> eps(ref(option_delta_length) = (ref(option_header) & 0b00001111)) 
                        //option optional delta
                        >> (
                              (  eps(ref(delta) <= 12)  
                              | (eps(ref(delta) == 13) >> byte_[ref(delta) += _1]) 
                              | (eps(ref(delta) == 14) >> word[ref(delta) = (_1 + 255)]) //can overflow
                              ) 
                              >> eps[ref(option.number) += ref(delta)]
                              //internal
                              >> eps[clear(phnx::ref(option.values))]
                            )

                        //option optional value length
                        >> (  
                              (eps(ref(option_delta_length) <= 12) 
                              | (eps(ref(option_delta_length) == 13) >> byte_[ref(option_delta_length) += _1]) 
                              | (eps(ref(option_delta_length) == 14) >> word[ref(option_delta_length) = (_1 + 255)]) //can overflow
                              )

                              //option value
                              >> repeat(ref(option_delta_length))[byte_[push_back(phnx::ref(option.values),_1)]]  
                           )


                          //adding option to option list
                          >> eps[push_back(phnx::ref(msg.options),phnx::ref(option))]
                       )
                     )
                 )
              ));

    msg.version = (coap_header & 0b11000000) >> 6;
    msg.type = (coap_header & 0b00110000) >> 4;
    msg.code_class = (coap_code & 0b11100000) >> 5;
    msg.code_detail = (coap_code & 0b00011111);

    return r;
  

};

int main(int argc, char **argv)
{

  coap_message m;
  
  std::vector<uint8_t> v{0b01110011, //version - type - token length
                         0b11111111, //code
                         0b11111111, // -message id
                         0b11111111, // -
                         0b11111111, // -token
                         0b11111111, // -
                         0b11111111, // -
                         0b11000010, // option header
                         0b00000001, // -option value
                         0b00011111, // -
                         0b10000011, // option header
                         0b00000010, // -option value
                         0b00000100, // -
                         0b00001000, // -
                         0b11010001, // option header
                         0b00000001, // -option optional delta
                         0b11111111, // option value
                         0b11111111, // payload marker
                         0b00001000, // -payload
                         0b00010000, // -
                         0b00100000, // -
                         0b01000000, // -
                         0b10000000, // -
                        }; 

  auto p = coap_message_parser(v.begin(),v.end(),m);

  if(!p)
  {
  std::cout << "Parsing FAIL" << std::endl;
  }
  std::cout << "Version=" << (int)m.version << " Type=" << (int)m.type << " "<< " Class=" << (int)m.code_class << " Detail=" << (int)m.code_detail << " ID=" << (int)m.message_id<< std::endl;
  for(auto &el:m.token)
  {
  std::cout << "Token val=" << (int)el << std::endl;
  }

  for(auto &pel:m.options)
  {
  std::cout << "Option number=" << pel.number << std::endl;
    for(auto &it:pel.values)
    {
      std::cout << "Val=" << (int)it << std::endl;
    }
  }

  for(auto &l:m.payload)
  {
      std::cout << "Payload=" << (int)l << std::endl;
  }
  return 0;
}
