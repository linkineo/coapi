#include <coapi.hpp>

typedef std::vector<coapi::coap_message> test_list;

using namespace coapi;

void test_1(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xABCD)
   .token("BCAFF")
   .add_option(option_registry::uri_path,"hello");
  
  tests.push_back(m.raw());
}

void test_2(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xDDBA)
   .token("BCAFFHH")
   .add_option(option_registry::location_path,"world")
   .add_option(option_registry::uri_path,"new");
  
  tests.push_back(m.raw());
}

void test_3(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xAAAA)
   .token("AAAA")
   .add_option(option_registry::location_path,"a")
   .add_option(option_registry::location_path,"a");
  
  tests.push_back(m.raw());
}

void test_4(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xFADC)
   .token("AAAA")
   .add_option(option_registry::uri_port,"makecoap")
   .add_option(option_registry::location_path,"great");
  
  tests.push_back(m.raw());
}

void test_5(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::service_unavailable)  
   .id(0xCCCC)
   .token("ABCDEFGH");
   
  tests.push_back(m.raw());
}

void test_6(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xAAAA)
   .token("AAAA")
   .add_option(option_registry::uri_port,"a")
   .add_option(option_registry::if_none_match,"g");
  
  tests.push_back(m.raw());
}

void test_7(test_list &tests)
{
  message m;
  
  m.type(coap_type::non_confirmable)
   .code(code_registry::GET)  
   .id(0xAAAA)
   .token("AAAABBBB");
  
  tests.push_back(m.raw());
}

void test_8(test_list &tests)
{
  message m;
  
  m.type(coap_type::reset)
   .code(code_registry::unauthorized)  
   .id(0xAAAA)
   .token("AAAABBBB");
  
  tests.push_back(m.raw());
}

void test_9(test_list &tests)
{
  message m;
  
  m.type(coap_type::reset)
   .code(code_registry::unauthorized)  
   .id(0x62AB)
   .token("AQ")
   .payload("STAIRWAYTOHEAVEN");
  
  tests.push_back(m.raw());
}

void test_10(test_list &tests)
{
  message m;
  
  m.type(coap_type::non_confirmable)
   .code(code_registry::valid)  
   .id(0xDBCA)
   .token("HEHE")
   .add_option(option_registry::uri_path,"tonightim")
   .add_option(option_registry::content_format,"gonnahave")
   .payload("myselfarealgoodtime");
   
  tests.push_back(m.raw());
}

void test_11(test_list &tests)
{
  message m;
  
  m.type(coap_type::acknowledgement)
   .code(code_registry::created)  
   .id(0xACAB)
   .token("LAND")
   .add_option(option_registry::uri_path,"a")
   .add_option(option_registry::proxy_uri,"b");
   
  tests.push_back(m.raw());
}

void test_12(test_list &tests)
{
  message m;
  
  m.type(coap_type::acknowledgement)
   .code(code_registry::created)  
   .id(0xACAB)
   .token("LAND");
   
  auto m_in = m.raw();

  coapi::coap_option o_in;
  o_in.number=160;

  std::string vals("a");
  o_in.values = coapi::bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=500;

  std::string vals2("b");
  o_in2.values = coapi::bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_13(test_list &tests)
{
  message m;
  
  m.type(coap_type::non_confirmable)
   .code(code_registry::not_acceptable)  
   .id(0xEEEE)
   .token("HEHEHEHE")
   .add_option(option_registry::uri_path,"tonightim")
   .add_option(option_registry::uri_path,"gonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtime")
   .add_option(option_registry::size1,"theres")
   .payload("itsagodawfulsmallaffairforthegirlwiththemouseyhair");
  
  auto m_in = m.raw();

  coapi::coap_option o_in4;
  o_in4.number=500;

  std::string vals4("nostoppingme");
  o_in4.values = coapi::bytes(vals4.begin(),vals4.end());
  m_in.options.push_back(o_in4);

  coapi::coap_option o_in5;
  o_in5.number=1000;

  std::string vals5("t");
  o_in5.values = coapi::bytes(vals5.begin(),vals5.end());
  m_in.options.push_back(o_in5);

  tests.push_back(m_in);
}



