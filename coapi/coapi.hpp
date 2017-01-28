#ifndef COAPY_HPP
#define COAPY_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_container.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/qi_eps.hpp>

#include <frame_detail.hpp>

namespace coapi {

namespace qi = boost::spirit::qi;

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
                        eps[ref(delta) = (ref(option_header) >> 4 )] >> eps(ref(option_delta_length) = (ref(option_header) & 0b00001111)) 
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
    msg.type = (coap_header & 0b00110000) >> 4;
    msg.code_class = (coap_code & 0b11100000) >> 5;
    msg.code_detail = (coap_code & 0b00011111);

    return r;
};
}

#endif 
