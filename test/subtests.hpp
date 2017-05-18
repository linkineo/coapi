#include <iostream>
#include <coapi.hpp>

typedef std::vector<coapi::message> test_list;

using namespace coapi;

void test_1(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::GET)  
   .id(0xABCD)
   .token("BCAFF")
   .add_option(option_registry::uri_path,"hello");
  
  tests.push_back(m);
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
  
  tests.push_back(m);
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
  
  tests.push_back(m);
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
  
  tests.push_back(m);
}

void test_5(test_list &tests)
{
  message m;
  
  m.type(coap_type::confirmable)
   .code(code_registry::service_unavailable)  
   .id(0xCCCC)
   .token("ABCDEFGH");
   
  tests.push_back(m);
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
  
  tests.push_back(m);
}

void test_7(test_list &tests)
{
  message m;
  
  m.type(coap_type::non_confirmable)
   .code(code_registry::GET)  
   .id(0xAAAA)
   .token("AAAABBBB");
  
  tests.push_back(m);
}

void test_8(test_list &tests)
{
  message m;
  
  m.type(coap_type::reset)
   .code(code_registry::unauthorized)  
   .id(0xAAAA)
   .token("AAAABBBB");
  
  tests.push_back(m);
}

void test_9(test_list &tests)
{
  message m;
  
  m.type(coap_type::reset)
   .code(code_registry::unauthorized)  
   .id(0x62AB)
   .token("AQ")
   .payload("STAIRWAYTOHEAVEN");
  
  tests.push_back(m);
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
   
  tests.push_back(m);
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
   
  tests.push_back(m);
}

void test_12(test_list &tests)
{
  message m;
  
  m.type(coap_type::non_confirmable)
   .code(code_registry::not_acceptable)  
   .id(0xEEEE)
   .token("HEHEHEHE")
   .add_option(option_registry::uri_path,"tonightim")
   .add_option(option_registry::uri_path,"gonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtime")
   .add_option(option_registry::size1,"theres")
   .add_option(option_registry::uri_path,"nostoppingme")
   .add_option(option_registry::proxy_uri,"t")
   .payload("itsagodawfulsmallaffairforthegirlwiththemouseyhair");
  
  tests.push_back(m);
}

void test_13(test_list &tests)
{
  message m;

  m.type(coap_type::confirmable)
   .code(code_registry::GET)
   .id(0xABCD)
   .token("BCAFF")
   .uri("hello/world/myself&test=5&pillow=3&world=6");

  assert(m.uri() == "/hello/world/myself&test=5&pillow=3&world=6");
 
  tests.push_back(m);
}

