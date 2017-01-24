#include <cantcoap.cpp>
#include <vector>
#include <iostream>
#include <bitset>

#include <subtests.hpp>
#include <coapy.hpp>

void compare_frames(coapy::coap_message m_in, coapy::coap_message m_out)
{
   assert(m_out.type == m_in.type);
   assert(m_out.code_class == m_in.code_class);
   assert(m_out.code_detail == m_in.code_detail);
   assert(m_out.message_id == m_in.message_id);
   assert(std::equal(m_out.token.begin(),m_out.token.end(),m_in.token.begin()));

   assert(m_out.options.size() == m_in.options.size()); 
   assert(std::equal(m_out.options.begin(),m_out.options.end(),m_in.options.begin(),[](coapy::coap_option out, coapy::coap_option in)
     { return(out.number == in.number &&
       std::equal(out.values.begin(),out.values.end(),in.values.begin()));
     }));

   assert(m_out.payload.size() == m_in.payload.size()); 
   assert(std::equal(m_out.payload.begin(),m_out.payload.end(),m_in.payload.begin()));
}

void create_reference_frame(const coapy::coap_message m_in,bytes &reference_frame)
{
  CoapPDU *pdu = new CoapPDU(); 
  pdu->setVersion(m_in.version);
  pdu->setType((CoapPDU::Type)m_in.type);
  pdu->setCode(CoapPDU::Code((m_in.code_class << 5) + m_in.code_detail));
  pdu->setToken((uint8_t*)&m_in.token[0],m_in.token.size());
  pdu->setMessageID(m_in.message_id);

  for(auto &opt:m_in.options)
  { 
  pdu->addOption(opt.number,opt.values.size(),(uint8_t*)&(opt.values[0]));
  }
  reference_frame = bytes(pdu->getPDUPointer(),pdu->getPDUPointer()+pdu->getPDULength());
}

void print_frame(const bytes frame)
{
  std::cout << "--------" << std::endl; 
  std::cout << "---FRAME" << std::endl; 
  for(auto &l:frame)
  {
    std::cout << std::bitset<8>(l) << std::endl;
  }
  std::cout << "--------" << std::endl; 
}

int perform_tests(const test_list &tests, bool debug)
{

  for(auto &el:tests)
  {
    bytes frame;
    coapy::coap_message m_out;
    create_reference_frame(el,frame);

    if(debug)
    {
      print_frame(frame);
    }

    if(coapy::coap_message_parser(frame.begin(),frame.end(),m_out))
    {
      compare_frames(el,m_out);
      std::cout << "Subtest passed..." << std::endl;
    }
    else
    {
      std::cout << "Parse error" << std::endl;
      return 1;
    }
  }

  std::cout << "All tests OK :-)" << std::endl;
  return 0;

}


int main(int argc, char** argv)
{
  test_list tests;

  test_1(tests);
  test_2(tests);
  test_3(tests);

  return perform_tests(tests,true);
}
