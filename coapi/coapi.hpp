#ifndef COAPY_HPP
#define COAPY_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_container.hpp>

#include <frame_detail.hpp>

namespace coapi {

namespace qi = boost::spirit::qi;
namespace ka = boost::spirit::karma;

template <typename OutputIterator>
bool coap_message_generator(OutputIterator out,const coapi::coap_message &msg)
{
    using ka::generate;
    using ka::byte_;
    using ka::big_word;
    using ka::hex;
    using ka::eps;
    using boost::phoenix::ref;
    using boost::phoenix::size;
    using boost::phoenix::at;
    using boost::phoenix::clear;
    using ka::_1;
    using ka::repeat;

    namespace phnx = boost::phoenix;
    
    uint8_t coap_header = 0;
    uint8_t options_header = 0;
  
    coap_header += (msg.version << 6);
    coap_header += (uint8_t)msg.type;
    coap_header += msg.token.size();
 
    uint8_t token_at = 0;
    uint8_t payload_at = 0;
    uint32_t options_at = 0;
    uint32_t option_at = 0;
    uint32_t delta = 0;     

    uint16_t number = 0;

    coapi::coap_option option{}; 

    return generate(out,
           (
           byte_[_1 = ref(coap_header)] 
           << byte_[_1 = ref(msg.code)]
           << big_word[_1 = ref(msg.message_id)]
           << repeat(size(phnx::ref(msg.token)))[byte_[_1 = phnx::ref(msg.token)[phnx::ref(token_at)++]]]
           
           << repeat(msg.options.size())[
                eps[phnx::ref(option) = at(phnx::ref(msg.options),phnx::ref(options_at)++)] << eps[phnx::ref(delta) = (phnx::ref(option.number) - phnx::ref(number))] << eps[phnx::ref(number) = phnx::ref(option.number)] 
                << eps[phnx::ref(option_at) = 0]
 
                << ( (eps(phnx::ref(delta) < 13) << eps[phnx::ref(options_header) = (phnx::ref(delta) << 4)])
                     | (eps(phnx::ref(delta) >= 13) << eps(phnx::ref(delta) < 269) << eps[phnx::ref(options_header) = (13 << 4)])
                     | (eps(phnx::ref(delta) >= 269) << eps[phnx::ref(options_header) = (14 << 4)])
                   ) 

                << ( (eps(size(phnx::ref(option.values)) < 13) << eps[phnx::ref(options_header) += size(phnx::ref(option.values))]) 
                     | (eps(size(phnx::ref(option.values)) >= 13) << eps(size(phnx::ref(option.values)) < 269) << eps[phnx::ref(options_header) += 13])
                     | (eps(size(phnx::ref(option.values)) >= 269) << eps[phnx::ref(options_header) += 14])
                   )
                << byte_(phnx::ref(options_header))
                << -(eps(phnx::ref(delta) >= 13) << eps(phnx::ref(delta) < 269) << byte_((phnx::ref(delta) - 13)))
                << -(eps(phnx::ref(delta) >= 269) << big_word((phnx::ref(delta) - 269)))
                << -(eps(size(phnx::ref(option.values)) >= 13) << eps(size(phnx::ref(option.values)) < 269) << byte_(size(phnx::ref(option.values)) - 13)) 
                << -(eps(size(phnx::ref(option.values)) >= 269)  << big_word(size(phnx::ref(option.values)) - 269)) 
             
                << repeat(size(phnx::ref(option.values)))[byte_[_1 = phnx::ref(option.values)[phnx::ref(option_at)++]]] 
              ]

           << (eps(msg.payload.size()) << byte_(0xFF)
               << repeat(msg.payload.size())[byte_[_1 = phnx::ref(msg.payload)[phnx::ref(payload_at)++]]]
              )
           ));
}

template <typename Iterator>
bool coap_message_parser(Iterator first, Iterator last, coapi::coap_message &msg)
{
    using qi::byte_;
    using qi::big_word;
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

    coapi::coap_option option{};   
 
    bool r = parse(first, last, 
             (
              //header version:2-type:2-tag length:4
              byte_[ref(coap_header) = _1]
    
              //code:8
              >> byte_[ref(coap_code) = _1]

              //message id:16
              >> big_word[ref(msg.message_id) = _1]

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
                        eps[ref(delta) = (ref(option_header) >> 4 )] >> eps[ref(option_delta_length) = (ref(option_header) & 0b00001111)]
                        //option optional delta
                        >> (
                              (  eps(ref(delta) <= 12)  
                              | (eps(ref(delta) == 13) >> byte_[ref(delta) += _1]) 
                              | (eps(ref(delta) == 14) >> big_word[ref(delta) += (_1 + 255)]) //can overflow
                              ) 
                              >> eps[ref(option.number) += ref(delta)]
                              //internal
                              >> eps[clear(phnx::ref(option.values))]
                            )

                        //option optional value length
                        >> (  
                              (eps(ref(option_delta_length) <= 12) 
                              | (eps(ref(option_delta_length) == 13) >> byte_[ref(option_delta_length) += _1]) 
                              | (eps(ref(option_delta_length) == 14) >> big_word[ref(option_delta_length) += (_1 + 255)]) //can overflow
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
    msg.type = (coapi::coap_type)((coap_header & 0b00110000));
    msg.code = (coapi::code_registry)coap_code;

    return r;
};
}

#endif 
