#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <iostream>
#include <string>
#include <vector>


namespace qi = boost::spirit::qi;

struct coap_payload {
 std::vector<uint8_t> bytes; 
};

struct coap_option {
  uint8_t delta : 4;
  uint8_t length :4;
  uint16_t delta_extended;
  uint16_t length_extended;

  std::vector<uint8_t> value;
};

struct coap_message {

  //byte 0
  uint8_t version; //:2;
  uint8_t type;    //:2;
                   //:4

  //byte 1
  uint8_t code_class; //:3;
  uint8_t code_detail;//:5;

  //bytes 2&3
  uint16_t message_id;

  std::vector<uint8_t> token;
  
  //coap_option option;
  //coap_payload payload;
};

template <typename Iterator>
bool coap_message_parser(Iterator first, Iterator last, coap_message &msg)
{
    using qi::byte_;
    using qi::word;
    using boost::phoenix::ref;
    using boost::phoenix::push_back;
    using qi::_1;
    using qi::parse;
    using qi::repeat;   

    namespace phnx = boost::phoenix;
 
    uint8_t coap_header = 0;
    uint8_t coap_code = 0;
    
    bool r = parse(first, last, 
             (
              byte_[ref(coap_header) = _1]
              >> byte_[ref(coap_code) = _1]
              >> word[ref(msg.message_id) = _1]
              >> repeat((ref(coap_header) & 0b00001111))[byte_[push_back(phnx::ref(msg.token),_1)]]
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
  std::vector<uint8_t> v{0b01110011,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111,0b11111111}; 

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
  return 0;
}
