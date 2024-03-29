#include "util.h"

auto mime_type(beast::string_view path) -> beast::string_view {
  using beast::iequals;
  auto const ext = [&path] {
    auto const pos = path.rfind(".");
    if (pos == beast::string_view::npos)
      return beast::string_view{};
    return path.substr(pos);
  }();
  if (iequals(ext, ".htm"))
    return "text/html";
  if (iequals(ext, ".html"))
    return "text/html";
  if (iequals(ext, ".php"))
    return "text/html";
  if (iequals(ext, ".css"))
    return "text/css";
  if (iequals(ext, ".txt"))
    return "text/plain";
  if (iequals(ext, ".js"))
    return "application/javascript";
  if (iequals(ext, ".json"))
    return "application/json";
  if (iequals(ext, ".xml"))
    return "application/xml";
  if (iequals(ext, ".swf"))
    return "application/x-shockwave-flash";
  if (iequals(ext, ".flv"))
    return "video/x-flv";
  if (iequals(ext, ".png"))
    return "image/png";
  if (iequals(ext, ".jpe"))
    return "image/jpeg";
  if (iequals(ext, ".jpeg"))
    return "image/jpeg";
  if (iequals(ext, ".jpg"))
    return "image/jpeg";
  if (iequals(ext, ".gif"))
    return "image/gif";
  if (iequals(ext, ".bmp"))
    return "image/bmp";
  if (iequals(ext, ".ico"))
    return "image/vnd.microsoft.icon";
  if (iequals(ext, ".tiff"))
    return "image/tiff";
  if (iequals(ext, ".tif"))
    return "image/tiff";
  if (iequals(ext, ".svg"))
    return "image/svg+xml";
  if (iequals(ext, ".svgz"))
    return "image/svg+xml";
  return "application/text";
}

auto path_cat(boost::beast::string_view base, boost::beast::string_view path)
    -> std::string {
  if (base.empty())
    return std::string(path);
  std::string result(base);
  char constexpr path_separator = '/';
  if (result.back() == path_separator)
    result.resize(result.size() - 1);
  result.append(path.data(), path.size());
  return std::filesystem::absolute(result);
}

auto log_error(boost::beast::error_code error_code, const char *what) -> void {
  std::cerr << what << ":" << error_code.message() << "\n";
}

auto path_exist(std::string path) -> bool { return fs::exists(path); }

auto path_is_dir(std::string path) -> bool { return fs::is_directory(path); }

auto path_is_file(std::string path) -> bool {
  return fs::is_regular_file(path);
}

auto read_dir(std::string path) -> std::vector<fs::directory_entry> {
  std::vector<fs::directory_entry> result;
  if (path_is_dir(path)) {
    for (auto &p : fs::directory_iterator(path)) {
      result.push_back(p);
    }
  }
  return result;
}