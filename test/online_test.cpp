#include <boost/asio.hpp>
#include <subtests.hpp>
#include <iostream>
#include <coapi.hpp>

void online_test(const std::vector<uint8_t> bytes)
{
  using boost::asio::ip::udp;
  boost::asio::io_service ios;
  udp::resolver resolver(ios);
  udp::resolver::query query(udp::v4(),"coap.me","5683");
  udp::endpoint receiver_endpoint = *resolver.resolve(query);
 
  udp::socket socket(ios);
  socket.open(udp::v4());

  socket.send_to(boost::asio::buffer(bytes),receiver_endpoint);
  
  std::vector<uint8_t> rep_bytes(128);
  
  udp::endpoint reply_endpoint;
  size_t len = socket.receive_from(boost::asio::buffer(rep_bytes),reply_endpoint); 
  
  rep_bytes.resize(len);
  
  /*for(auto &p:rep_bytes)
  {
  std::cout << std::bitset<8>(p) << std::endl;
  }*/ 
  
  coapi::coap_message msg{};
  coapi::coap_message_parser(rep_bytes.begin(),rep_bytes.end(),msg);
  
  
  for(auto &el:msg.payload)
  {
  std::cout << el; 
  }
  
 
}


int main(int argc, char** argv)
{
  coapi::message msg;
  
  msg.type(coap_type::confirmable)
     .code(code_registry::GET)
     .id(0xAAAA)
     .token("BBBB")
     .uri("test");


  std::vector<uint8_t> bytes{};
  std::back_insert_iterator<std::vector<uint8_t>> it(bytes);
  auto ok = coapi::coap_message_generator(it,msg.raw());

  online_test(bytes);
  
  return 1;
}
