/*
 * Descent 3
 * Copyright (C) 2024 Descent Developers
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "httpclient.h"

#ifdef _UWP
extern "C" __declspec(dllimport) void uwp_GetBundleFilePath(char *buf, const char* file);
#endif

namespace D3 {

HttpClient::HttpClient(const std::string &URL) {
  m_client = std::make_unique<httplib::Client>(URL);
#ifdef _UWP
  char buf[256];
  uwp_GetBundleFilePath(buf, "cacert.pem");
  m_client->set_ca_cert_path(buf);
#endif
  m_client->set_follow_location(true);  // Follow redirects
  m_client->set_connection_timeout(5, 0); // 5 sec timeout
}

httplib::Result HttpClient::Get(const std::string &URIPath) {
    return m_client->Get(URIPath);
}

httplib::Result HttpClient::Get(const std::string &URIPath, const D3::HttpClient::Progress &progress) {
  return m_client->Get(URIPath, progress);
}

httplib::Result HttpClient::Get(const std::string &URIPath, const httplib::ContentReceiver &content_receiver) {
  return m_client->Get(URIPath, content_receiver);
}

httplib::Result HttpClient::Get(const std::string &URIPath, const httplib::ContentReceiver &content_receiver,
                    const D3::HttpClient::Progress &progress) {
  return m_client->Get(URIPath, content_receiver, progress);
}

void HttpClient::SetProxy(const std::string &proxy_host, uint16_t port) {
  m_client->set_proxy(proxy_host, port);
}

}
