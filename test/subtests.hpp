#include <coapi.hpp>

typedef std::vector<uint8_t> bytes;
typedef std::vector<coapi::coap_message> test_list;

void test_1(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::GET;
  
  m_in.message_id = 0xABCD; // 2 bytes

  std::string tok("BCAFF"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=11; 

  std::string vals("hello"); 
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);


  tests.push_back(m_in);
}

void test_2(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::GET;
  
  m_in.message_id = 0xDDBA; // 2 bytes

  std::string tok("BCAFFHH"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=10;

  std::string vals("world"); 
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=11;

  std::string vals2("new");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_3(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::GET;

  m_in.message_id = 0xAAAA; // 2 bytes

  std::string tok("AAAA"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=10;

  std::string vals("a");   
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=10;

  std::string vals2("a");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_4(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::GET;

  m_in.message_id = 0xFADC; // 2 bytes

  std::string tok("AAAA"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=7;

  std::string vals("makecoap");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=10;

  std::string vals2("great");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);

  tests.push_back(m_in);
}

void test_5(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::service_unavailable;

  m_in.message_id = 0xCCCC; // 2 bytes

  std::string tok("ABCDEFGH"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  tests.push_back(m_in);
}

void test_6(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::confirmable;
  m_in.code = coapi::code_registry::GET;

  m_in.message_id = 0xAAAA; // 2 bytes

  std::string tok("AAAA"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=7;

  std::string vals("a");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=6;

  std::string vals2("b");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);

  tests.push_back(m_in);
}

void test_7(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::non_confirmable;
  m_in.code = coapi::code_registry::GET;

  m_in.message_id = 0xAAAA; // 2 bytes

  std::string tok("AAAABBBB"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  tests.push_back(m_in);
}

void test_8(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::reset;
  m_in.code = coapi::code_registry::unauthorized;

  m_in.message_id = 0xAAAA; // 2 bytes

  std::string tok("AAAABBBB"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  tests.push_back(m_in);
}

void test_9(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::reset;
  m_in.code = coapi::code_registry::unauthorized;

  m_in.message_id = 0x62AB; // 2 bytes

  std::string tok("AQ"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  std::string pl("STAIRWAYTOHEAVEN");
  m_in.payload.insert(m_in.payload.begin(),pl.begin(),pl.end());
  
  tests.push_back(m_in);
}

void test_10(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::non_confirmable;
  m_in.code = coapi::code_registry::valid;

  m_in.message_id = 0xDBCA; // 2 bytes

  std::string tok("HEHE"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=10;

  std::string vals("tonightim");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=12;

  std::string vals2("gonnahave");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);

  std::string pl("myselfarealgoodtime");
  m_in.payload.insert(m_in.payload.begin(),pl.begin(),pl.end());

  tests.push_back(m_in);
}

void test_11(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::acknowledgement;
  m_in.code = coapi::code_registry::created;

  m_in.message_id = 0xACAB; // 2 bytes

  std::string tok("LAND"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=10;

  std::string vals("a");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=25;

  std::string vals2("b");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_12(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::acknowledgement;
  m_in.code = coapi::code_registry::created;

  m_in.message_id = 0xACAB; // 2 bytes

  std::string tok("LAND"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=160;

  std::string vals("a");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=500;

  std::string vals2("b");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_13(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = coapi::coap_type::non_confirmable;
  m_in.code = coapi::code_registry::not_acceptable;

  m_in.message_id = 0xEEEE; // 2 bytes

  std::string tok("HEHEHEHE"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapi::coap_option o_in;
  o_in.number=10;

  std::string vals("tonightim");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapi::coap_option o_in2;
  o_in2.number=10;

  std::string vals2("gonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtimegonnahavetonightarealgoodtime");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);

  coapi::coap_option o_in3;
  o_in3.number=60;

  std::string vals3("theres");
  o_in3.values = bytes(vals3.begin(),vals3.end());
  m_in.options.push_back(o_in3);

  coapi::coap_option o_in4;
  o_in4.number=500;

  std::string vals4("nostoppingme");
  o_in4.values = bytes(vals4.begin(),vals4.end());
  m_in.options.push_back(o_in4);

  coapi::coap_option o_in5;
  o_in5.number=1000;

  std::string vals5("t");
  o_in5.values = bytes(vals5.begin(),vals5.end());
  m_in.options.push_back(o_in5);


  std::string pl("itsagodawfulsmallaffairforthegirlwiththemouseyhair");
  m_in.payload.insert(m_in.payload.begin(),pl.begin(),pl.end());

  tests.push_back(m_in);
}



