#include <cantcoap.cpp>
#include <vector>
#include <iostream>
#include <bitset>

#include <coapy.hpp>

typedef std::vector<uint8_t> bytes;

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

  pdu->addOption(m_in.options[0].number,m_in.options[0].values.size(),(uint8_t*)&(m_in.options[0].values[0]));
  
  reference_frame = bytes(pdu->getPDUPointer(),pdu->getPDUPointer()+pdu->getPDULength());
}

int main(int argc, char** argv)
{

  coapy::coap_message m_in,m_out;
 
  m_in.version = 1;
  m_in.type = CoapPDU::COAP_CONFIRMABLE;
  m_in.code_class = 0;
  m_in.code_detail = 1;
  m_in.message_id = 0xABCD;
  
  std::string tok("BCAFF");
  m_in.token = bytes(tok.begin(),tok.end());
  
  coapy::coap_option o_in;
  o_in.number=11;
  
  std::string vals("hello");
  o_in.values = bytes(vals.begin(),vals.end());
  m_in.options.push_back(o_in);
  
  bytes frame;
  create_reference_frame(m_in,frame);

  if(coapy::coap_message_parser(frame.begin(),frame.end(),m_out))
  {
   compare_frames(m_in,m_out);
  }
  else
  {
   std::cout << "Parse error" << std::endl;
   return 1;
  }

  return 0;
}
