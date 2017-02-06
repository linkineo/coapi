#ifndef COAP_CODES_HPP
#define COAP_CODES_HPP

namespace coapi {

enum cc : uint8_t
{ 
  method = 0,
  success = (2<<5), 
  client_error = (4 << 5),
  server_error = (5 << 5)
};


enum coap_type : uint8_t {
  confirmable = 0,
  non_confirmable = (1 << 4),
  acknowledgement = (2 << 4),
  reset = (3 << 4)
};

enum code_registry : uint8_t {
  empty = 0,

  GET = cc::method + 1,
  POST = cc::method + 2,
  PUT = cc::method + 3,
  DEL = cc::method + 4,
  
  created = cc::success + 1,
  deleted = cc::success + 2,
  valid = cc::success + 3,
  changed = cc::success + 4,
  content = cc::success + 5,
  
  bad_request = cc::client_error + 0,
  unauthorized = cc::client_error + 1,
  bad_option = cc::client_error + 2,
  forbidden = cc::client_error + 3,
  not_found = cc::client_error + 4,
  method_not_allowed = cc::client_error + 5,
  not_acceptable = cc::client_error + 6, 
  precondition_failed = cc::client_error + 12,
  request_entity_too_large = cc::client_error + 13,
  unsupported_content_format = cc::client_error + 15,
  
  internal_server_error = cc::server_error + 0,
  not_implemented = cc::server_error + 1,
  bad_gateway = cc::server_error + 2,
  service_unavailable = cc::server_error + 3,
  gateway_timeout = cc::server_error + 4, 
  proxying_not_supported = cc::server_error + 5
};

enum option_registry : uint16_t {
  reserved_zero = 0,
  if_match = 1,
  uri_host = 3,
  etag = 4,
  if_none_match = 5,
  uri_port = 7, 
  location_path = 8,
  uri_path = 11, 
  content_format = 12,
  max_age = 14,
  uri_query = 15,
  accept = 17,
  location_query = 20,
  proxy_uri = 35,
  proxy_scheme = 39,
  size1 = 60
};

}

#endif
