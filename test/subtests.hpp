#include <coapi.hpp>

typedef std::vector<uint8_t> bytes;
typedef std::vector<coapi::coap_message> test_list;

void test_1(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;
  
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
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;
  
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
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;

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
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;

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
  m_in.type = 0;
  m_in.code_class = 5;
  m_in.code_detail = 3;

  m_in.message_id = 0xCCCC; // 2 bytes

  std::string tok("ABCDEFGH"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  tests.push_back(m_in);
}

void test_6(test_list &tests)
{
  coapi::coap_message m_in;

  m_in.version = 1;
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;

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
