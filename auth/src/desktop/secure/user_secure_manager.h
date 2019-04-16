// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FIREBASE_AUTH_CLIENT_CPP_SRC_DESKTOP_SECURE_USER_SECURE_MANAGER_H_
#define FIREBASE_AUTH_CLIENT_CPP_SRC_DESKTOP_SECURE_USER_SECURE_MANAGER_H_

#include <string>

#include "app/memory/unique_ptr.h"
#include "app/src/include/firebase/future.h"
#include "app/src/reference_counted_future_impl.h"
#include "app/src/safe_reference.h"
#include "auth/src/desktop/secure/user_secure_data_handle.h"
#include "auth/src/desktop/secure/user_secure_internal.h"
#include "auth/src/desktop/secure/user_secure_linux_internal.h"

namespace firebase {
namespace auth {
namespace secure {

class UserSecureManager {
 public:
  explicit UserSecureManager();
  ~UserSecureManager();

  // Overloaded constructor to set the internal instance.
  explicit UserSecureManager(UniquePtr<UserSecureInternal> userSecureInternal);

  // Load persisted user data for given app name.
  Future<std::string> LoadUserData(const std::string& appName);

  // Save user data under the key of given app name.
  Future<void> SaveUserData(const std::string& appName,
                            const std::string& userData);

  // Delete user data under the given app name.
  Future<void> DeleteUserData(const std::string& appName);

  // Delete all user data.
  Future<void> DeleteAllData();

 private:
  UniquePtr<UserSecureInternal> user_secure_;
  ReferenceCountedFutureImpl future_api_;

  // Static scheduler to shared among all auth instance.
  scheduler::Scheduler scheduler_;

  // Safe reference to this.  Set in constructor and cleared in destructor
  // Should be safe to be copied in any thread because the SharedPtr never
  // changes, until safe_this_ is completely destroyed.
  typedef firebase::internal::SafeReference<UserSecureManager> ThisRef;
  typedef firebase::internal::SafeReferenceLock<UserSecureManager> ThisRefLock;
  ThisRef safe_this_;
};

}  // namespace secure
}  // namespace auth
}  // namespace firebase

#endif  // FIREBASE_AUTH_CLIENT_CPP_SRC_DESKTOP_SECURE_USER_SECURE_MANAGER_H_
