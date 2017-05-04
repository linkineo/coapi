#ifndef COAPY_FRAME_DETAILS_HPP
#define COAPY_FRAME_DETAILS_HPP

#include <algorithm>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <coap_codes.hpp>

namespace coapi {

struct coap_option {

  uint16_t number = option_registry::reserved_zero;
  std::vector<uint8_t> values;
};

typedef std::vector<uint8_t> coap_payload;
typedef std::vector<coap_option> coap_options_list;
typedef std::vector<uint8_t> bytes;

struct coap_message {

  uint8_t version = 1;
  uint8_t type;

  code_registry code;
  uint16_t message_id;

  std::vector<uint8_t> token;

  coap_options_list options;
  coap_payload payload;
};

void sort_options(coap_options_list &list)  
{
  std::sort(list.begin(), list.end(), [](coap_option a, coap_option b){
    return a.number < b.number;
  });
}

class message{

public:
  
  message(){}
  message(coap_message msg) : _msg(msg) {}

  coapi::coap_message raw()
  {
    return _msg;
  }
  
  uint8_t version()
  {
    return _msg.version;
  }

  coapi::message &type(coapi::coap_type t)
  {
    _msg.type = t;
    return *this;
  }

  coapi::coap_type type()
  {
    return (coapi::coap_type)_msg.type;
  }

  coapi::message &code(coapi::code_registry c)
  {
    _msg.code=c;
    return *this;
  }

  coapi::code_registry code()
  {
    return _msg.code;
  }

  coapi::message &id(uint16_t id)
  {
    _msg.message_id = id;
    return *this;
  }

  uint16_t id()
  {
    return _msg.message_id;
  }

  coapi::message &token(std::vector<uint8_t> t)
  {
    _msg.token = t;
    return *this;
  }

  coapi::message &token(uint64_t t)
  {
    _msg.token.clear();
    for(size_t p=0;p<7;p++)
    {
    uint8_t val = ((t >> (p*8)) & 0xFF);
    _msg.token.push_back(val);
    } 
    return *this; 
  }

  coapi::message &token(std::string s)
  {
    _msg.token = bytes(s.begin(),s.end());
    return *this;
  }
  
  std::vector<uint8_t> token()
  {
    return _msg.token;
  }
  
  uint64_t token_uint64()
  {
    uint64_t val;
    for(size_t p=0;p<7;p++)
    {
    val+= (uint64_t)(_msg.token[p] << (8*p));   
    }
    return val;
  }

  std::string token_string()
  {
    std::string val(_msg.token.begin(),_msg.token.end());
    return val;
  }
  
  coapi::message &add_option(option_registry number,bytes values)
  {
    coap_option option;
    option.number = number;
    option.values = values;
    _msg.options.push_back(option);
    sort_options(_msg.options);
    return *this;
  }

  coapi::message &add_option(option_registry number,std::string val)
  {
    coap_option option;
    option.number = number;
    bytes values(val.begin(),val.end());
    option.values = values;
    _msg.options.push_back(option);
    coapi::sort_options(_msg.options);
    return *this;
  }
  
  coap_options_list options()
  {
    return _msg.options;
  }

  coapi::message &uri(std::string val)
  {
    std::vector<std::string> tokens_slash;
    std::vector<std::string> tokens_ampersand;
    boost::split(tokens_slash, val, boost::is_any_of("/"));
    if(!tokens_slash.empty())
    {
     boost::split(tokens_ampersand, tokens_slash[tokens_slash.size()-1], boost::is_any_of("&"));
    }   
    
    for(int p=0;p<tokens_slash.size()-1;p++)
    {
      if(tokens_slash[p].size() < coapi::max_length_uri_path_query)
      {
        add_option(option_registry::uri_path,tokens_slash[p]);
      }
    }
    
    add_option(option_registry::uri_path,tokens_ampersand[0]);
    
    for(int p=1; p<tokens_ampersand.size();p++)
    { 
      if(tokens_ampersand[p].size() < coapi::max_length_uri_path_query)
      {
        add_option(option_registry::uri_query,tokens_ampersand[p]);
      }
    } 

    return *this;
  }
 
  std::string uri()
  { 
    std::string uri,uri_slashes,uri_ampersands;
    auto list = options();
    for(auto &option : list)
    {
      if(option.number == option_registry::uri_path)
      {
        std::string sls(option.values.begin(),option.values.end());
        uri_slashes += "/" + sls;         
      }

      if(option.number == option_registry::uri_query)
      {
        std::string amps(option.values.begin(),option.values.end());
        uri_ampersands += "&" + amps;
      } 
    }

    uri += uri_slashes + uri_ampersands;
    return uri;      
  }
  
  coapi::message &payload(coap_payload payload)
  {
    _msg.payload = payload;
    return *this;
  }
  
  coapi::message &payload(std::string payload)
  {
    coap_payload p(payload.begin(),payload.end());
    _msg.payload = p;
    return *this;
  }
  
  coap_payload payload()
  {
    return _msg.payload;
  }
  
private:
  coap_message _msg;
};

}

#endif
