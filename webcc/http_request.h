#ifndef WEBCC_HTTP_REQUEST_H_
#define WEBCC_HTTP_REQUEST_H_

#include <memory>
#include <string>

#include "webcc/http_message.h"

namespace webcc {

class HttpRequest : public HttpMessage {
 public:
  HttpRequest() = default;
  virtual ~HttpRequest() = default;

  const std::string& method() const { return method_; }
  void set_method(const std::string& method) { method_ = method; }

  const std::string& url() const { return url_; }
  void set_url(const std::string& url) { url_ = url; }

  const std::string& host() const { return host_; }
  const std::string& port() const { return port_; }

  // Set host name and port number.
  // The |host| is a descriptive name or a numeric IP address. The |port| is
  // a numeric number (e.g., "9000") and "80" will be used if it's empty.
  void SetHost(const std::string& host, const std::string& port);

  // Set start line according to HTTP method, URL, etc.
  void UpdateStartLine() override;

 private:
  // HTTP method.
  std::string method_;

  // Request URL.
  // A complete URL naming the requested resource, or the path component of
  // the URL.
  std::string url_;

  std::string host_;
  std::string port_;
};

typedef std::shared_ptr<HttpRequest> HttpRequestPtr;

}  // namespace webcc

#endif  // WEBCC_HTTP_REQUEST_H_
