#include <iostream>

#include <coapi.hpp>

int main(int argc, char **argv)
{

  coapi::coap_message m;
  
  std::vector<uint8_t> v{0b01110011, //version - type - token length
                         0b11111111, //code
                         0b11111111, // -message id
                         0b11111111, // -
                         0b00000001, // -token
                         0b00000010, // -
                         0b00000100, // -
                         0b11000010, // option header
                         0b00000001, // -option value
                         0b00011111, // -
                         0b10000011, // option header
                         0b00000010, // -option value
                         0b00000100, // -
                         0b00001000, // -
                         0b11010001, // option header
                         0b00000001, // -option optional delta
                         0b11111111, // option value
                         0b11111111, // payload marker
                         0b00001000, // -payload
                         0b00010000, // -
                         0b00100000, // -
                         0b01000000, // -
                         0b10000000, // -
                        }; 

  auto p = coap_message_parser(v.begin(),v.end(),m);

  if(!p)
  {
  std::cout << "Parsing FAIL" << std::endl;
  }
  std::cout << "Version=" << (int)m.version << " Type=" << (int)m.type << " "<< " Class=" << (int)m.code << " ID=" << (int)m.message_id<< std::endl;
  for(auto &el:m.token)
  {
  std::cout << "Token val=" << (int)el << std::endl;
  }

  for(auto &pel:m.options)
  {
  std::cout << "Option number=" << pel.number << std::endl;
    for(auto &it:pel.values)
    {
      std::cout << "Val=" << (int)it << std::endl;
    }
  }

  for(auto &l:m.payload)
  {
      std::cout << "Payload=" << (int)l << std::endl;
  }


  std::cout << "-------" << std::endl;
  std::cout << "Input vector" << std::endl;
  for(auto &el:v)
  {
  std::cout << std::bitset<8>(el) << std::endl;
  }

  std::cout << std::endl << std::endl;
  std::cout << "Output vector" << std::endl;

  std::vector<uint8_t> vv{};
  std::back_insert_iterator<std::vector<uint8_t>> it(vv);
  auto pp = coap_message_generator(it,m);
  for(auto &m:vv) 
  {
  std::cout << std::bitset<8>(m) << std::endl;
  }

  if(std::equal(v.begin(),v.end(),vv.begin()))
  {
    std::cout << "IN=OUT" << std::endl;
  }else
  {
    std::cout << "IN DIFFERENT FROM OUT" << std::endl;
  }
  
  return 0;
}
