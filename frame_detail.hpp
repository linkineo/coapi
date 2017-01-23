#ifndef COAPY_FRAME_DETAILS_HPP
#define COAPY_FRAME_DETAILS_HPP

#include <vector>

namespace coapy {

struct coap_option {

  uint16_t number = 0;
  std::vector<uint8_t> values;
};

typedef std::vector<uint8_t> coap_payload;
typedef std::vector<coap_option> coap_options_list;

struct coap_message {

  uint8_t version;
  uint8_t type;

  uint8_t code_class;
  uint8_t code_detail;

  uint16_t message_id;

  std::vector<uint8_t> token;

  coap_options_list options;
  coap_payload payload;
};

}

#endif
