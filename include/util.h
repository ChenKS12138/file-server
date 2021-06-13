#ifndef _INCLUDE_UTIL
#define _INCLUDE_UTIL

#include <boost/beast.hpp>
#include <iostream>

namespace beast = boost::beast;

// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
template <class Stream> struct send_lambda {
  Stream &stream_;
  bool &close_;
  beast::error_code &ec_;

  explicit send_lambda(Stream &stream, bool &close, beast::error_code &ec)
      : stream_(stream), close_(close), ec_(ec) {}

  template <bool isRequest, class Body, class Fields>
  void operator()(beast::http::message<isRequest, Body, Fields> &&msg) const {
    // Determine if we should close the connection after
    close_ = msg.need_eof();

    // We need the serializer here because the serializer requires
    // a non-const file_body, and the message oriented version of
    // http::write only works with const messages.
    beast::http::serializer<isRequest, Body, Fields> sr{msg};
    beast::http::write(stream_, sr, ec_);
  }
};

auto mime_type(beast::string_view path) -> beast::string_view;
auto path_cat(beast::string_view base, beast::string_view path) -> std::string;
auto log_error(beast::error_code error_code, char const *what) -> void;

#endif