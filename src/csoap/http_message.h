#ifndef CSOAP_HTTP_MESSAGE_H_
#define CSOAP_HTTP_MESSAGE_H_

#include <cassert>
#include <string>
#include "csoap/common.h"

namespace csoap {

class HttpHeader {
public:
  std::string name;
  std::string value;
};

// Base class for HTTP request and response messages.
class HttpMessage {
public:
  const std::string& start_line() const {
    return start_line_;
  }
  void set_start_line(const std::string& start_line) {
    start_line_ = start_line;
  }

  size_t content_length() const {
    return content_length_;
  }

  const std::string& content() const {
    return content_;
  }

  void SetHeader(const std::string& name, const std::string& value);

  // E.g., "text/xml; charset=utf-8"
  void SetContentType(const std::string& content_type) {
    SetHeader(kContentType, content_type);
  }

  void SetContentLength(size_t content_length) {
    content_length_ = content_length;
    SetHeader(kContentLength, std::to_string(content_length));
  }

  // Use move semantics to avoid copy.
  void set_content(std::string&& content) {
    content_ = std::move(content);
  }

  void AppendContent(const char* data, size_t count) {
    content_.append(data, count);
  }

  void AppendContent(const std::string& data) {
    content_.append(data);
  }

  bool IsContentFull() const {
    assert(IsContentLengthValid());
    return content_.length() >= content_length_;
  }

  bool IsContentLengthValid() const {
    return content_length_ != kInvalidLength;
  }

protected:
  HttpMessage() {
  }

protected:
  // Start line with trailing "\r\n".
  std::string start_line_;

  size_t content_length_ = kInvalidLength;

  std::vector<HttpHeader> headers_;

  std::string content_;
};

}  // namespace csoap

#endif  // CSOAP_HTTP_MESSAGE_H_
