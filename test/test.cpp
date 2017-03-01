#include <cantcoap.cpp>
#include <vector>
#include <iostream>
#include <bitset>

#include <subtests.hpp>
#include <coapi.hpp>

void compare_frames(coapi::coap_message m_in, coapi::coap_message m_out)
{
   coapi::sort_options(m_in.options);
   
   assert(m_out.type == m_in.type);
   assert(m_out.code == m_in.code);
   assert(m_out.message_id == m_in.message_id);
   assert(std::equal(m_out.token.begin(),m_out.token.end(),m_in.token.begin()));

   assert(m_out.options.size() == m_in.options.size()); 
   assert(std::equal(m_out.options.begin(),m_out.options.end(),m_in.options.begin(),[](coapi::coap_option out, coapi::coap_option in)
     { 
       return(out.number == in.number &&
       std::equal(out.values.begin(),out.values.end(),in.values.begin()));
     }));

   assert(m_out.payload.size() == m_in.payload.size()); 
   assert(std::equal(m_out.payload.begin(),m_out.payload.end(),m_in.payload.begin()));
}

void create_reference_frame(const coapi::coap_message m_in,coapi::bytes &reference_frame)
{
  CoapPDU *pdu = new CoapPDU(); 

  using namespace coapi;
  
  message m(m_in);

  pdu->setVersion(m.version());
  switch(m.type())
  {
    case coapi::coap_type::confirmable:
    pdu->setType((CoapPDU::Type::COAP_CONFIRMABLE));
    break;
    case coapi::coap_type::non_confirmable:
    pdu->setType((CoapPDU::Type::COAP_NON_CONFIRMABLE));
    break;
    case coapi::coap_type::acknowledgement:
    pdu->setType((CoapPDU::Type::COAP_ACKNOWLEDGEMENT));
    break;
    case coapi::coap_type::reset:
    pdu->setType((CoapPDU::Type::COAP_RESET));
    break;
  }
  pdu->setCode(CoapPDU::Code(m.code()));
  pdu->setToken((uint8_t*)&m.token()[0],m.token().size());
  pdu->setMessageID(m.id());

  for(auto &opt:m.options())
  { 
  pdu->addOption(opt.number,opt.values.size(),(uint8_t*)&(opt.values[0]));
  }

  pdu->setPayload((uint8_t*)&(m.payload()[0]),m.payload().size());


  reference_frame = coapi::bytes(pdu->getPDUPointer(),pdu->getPDUPointer()+pdu->getPDULength());
}

void print_frame(const coapi::bytes frame)
{
  int line=0;
  for(auto &l:frame)
  {
    std::cout << line << ":" << std::bitset<8>(l) << std::endl;
    line++;
  }
}

int perform_parser_tests(const test_list &tests, bool debug)
{

  std::cout << "------------" << std::endl;
  std::cout << "PARSER TESTS" << std::endl;
  int test = 1;
  for(auto el:tests)
  {
    coapi::bytes frame;
    coapi::coap_message m_out;
    create_reference_frame(el,frame);

      std::cout << std::endl << "---------PTest=" << test << std::endl;
    if(debug)
    {
      print_frame(frame);
    }

    if(coapi::coap_message_parser(frame.begin(),frame.end(),m_out))
    {
      compare_frames(el,m_out);
      std::cout << "Subtest passed..." << std::endl;
    }
    else
    {
      std::cout << "Parse error" << std::endl;
      return 1;
    }
    test++;
  }

  std::cout << "Performed n=" << tests.size() << " tests" <<std::endl;
  std::cout << "All PARSER tests OK :-)" << std::endl;
  return 0;

}


int perform_generator_tests(test_list &tests, bool debug)
{
  std::cout << "------------" << std::endl;
  std::cout << "PARSER TESTS" << std::endl;
  int test = 1; 
  for(auto el:tests)
  {
    coapi::bytes generated,reference;
    std::back_insert_iterator<coapi::bytes> genit(generated);

   // coapi::sort_options(el.options);
    create_reference_frame(el,reference);
    coapi::coap_message_generator(genit,el);

    std::cout << std::endl << "---------GTest=" << test << std::endl;
    
    if(debug)
    {
      std::cout << "------REF-------" << std::endl;
      print_frame(reference);
      std::cout << "------GEN-------" << std::endl;
      print_frame(generated);
    }

    for(int p=0;p<reference.size();p++)
    {
      if( reference[p] != generated[p] )
      {
        std::cout << "DIFF " << p << ":" << std::bitset<8>(reference[p]) << "--" << std::bitset<8>(generated[p]) << std::endl;
      }
    }

    assert(std::equal(reference.begin(),reference.end(),generated.begin()));
    std::cout << "Subtest passed" << std::endl;
    test++;
  }

  std::cout << "Performed n=" << tests.size() << " tests" <<std::endl;
  std::cout << "All GENERATOR tests OK :-)" << std::endl;
  return 0;
}

int main(int argc, char** argv)
{
  test_list tests;

  test_1(tests);
  test_2(tests);
  test_3(tests);
  test_4(tests);
  test_5(tests);
  test_6(tests);
  test_7(tests);
  test_8(tests);
  test_9(tests);
  test_10(tests);
  test_11(tests);
  test_12(tests);
  test_13(tests);

  perform_parser_tests(tests,true);
  perform_generator_tests(tests,true);
  
  return 0;
}
