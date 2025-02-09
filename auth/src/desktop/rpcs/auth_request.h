/*
 * Copyright 2018 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FIREBASE_AUTH_SRC_DESKTOP_RPCS_AUTH_REQUEST_H_
#define FIREBASE_AUTH_SRC_DESKTOP_RPCS_AUTH_REQUEST_H_

#include <string>

#include "app/rest/request_json.h"
#include "app/src/include/firebase/app.h"
#include "auth/request_generated.h"
#include "auth/request_resource.h"

namespace firebase {
namespace auth {

// Key name for header when sending language code data.
extern const char* kHeaderFirebaseLocale;

const char* const kHttps = "https://";

const char* const kHttp = "http://";

const char* const kServerURL =
    "www.googleapis.com/identitytoolkit/v3/relyingparty/";

const char* const kEmulatorLocalHost = "localhost";
const char* const kEmulatorPort = "9099";

class AuthRequest
    : public firebase::rest::RequestJson<fbs::Request, fbs::RequestT> {
 public:
  // App is a non-const parameter because this constructor might modify App's
  // internal HeartbeatController by logging or fetching heartbeats.
  AuthRequest(::firebase::App& app, const char* schema, bool deliver_heartbeat);

  AuthRequest(::firebase::App& app, const unsigned char* schema,
              bool deliver_heartbeat)
      : AuthRequest(app, reinterpret_cast<const char*>(schema),
                    deliver_heartbeat) {}

  std::string GetUrl();

 private:
  void CheckEmulator();
  std::string emulator_url;
};

}  // namespace auth
}  // namespace firebase

#endif  // FIREBASE_AUTH_SRC_DESKTOP_RPCS_AUTH_REQUEST_H_
