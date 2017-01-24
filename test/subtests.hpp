#include <coapy.hpp>

typedef std::vector<uint8_t> bytes;
typedef std::vector<coapy::coap_message> test_list;

void test_1(test_list &tests)
{
  coapy::coap_message m_in;

  m_in.version = 1;
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;
  
  m_in.message_id = 0xABCD; // 2 bytes

  std::string tok("BCAFF"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapy::coap_option o_in;
  o_in.number=11; 

  std::string vals("hello"); 
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);


  tests.push_back(m_in);
}

void test_2(test_list &tests)
{
  coapy::coap_message m_in;

  m_in.version = 1;
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;
  
  m_in.message_id = 0xDDBA; // 2 bytes

  std::string tok("BCAFFHH"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapy::coap_option o_in;
  o_in.number=10;

  std::string vals("world"); 
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapy::coap_option o_in2;
  o_in2.number=11;

  std::string vals2("new");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

void test_3(test_list &tests)
{
  coapy::coap_message m_in;

  m_in.version = 1;
  m_in.type = 0;
  m_in.code_class = 0;
  m_in.code_detail = 1;

  m_in.message_id = 0xAAAA; // 2 bytes

  std::string tok("AAAA"); //8 bytes max
  m_in.token = bytes(tok.begin(),tok.end());

  coapy::coap_option o_in;
  o_in.number=10;

  std::string vals("a");   
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);

  coapy::coap_option o_in2;
  o_in2.number=10;

  std::string vals2("a");
  o_in2.values = bytes(vals2.begin(),vals2.end());
  m_in.options.push_back(o_in2);


  tests.push_back(m_in);
}

