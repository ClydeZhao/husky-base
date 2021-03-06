// Copyright 2017 Husky Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <map>
#include <memory>

#include "zmq.hpp"

#include "husky-base/bin_stream.h"
#include "husky-base/mailbox_adress_book.h"
#include "husky-base/shard.h"

namespace husky {
namespace base {

class MailboxSender {
 public:
  MailboxSender(const MailboxAddressBook& addr_book, zmq::context_t* zmq_context);

  // This takes over the ownership of bin_stream
  void Send(Shard shard, int channel_id, int progress, BinStream* bin_stream);

  void SendComplete(int channel_id, int progress);

 protected:
  MailboxAddressBook addr_book_;
  zmq::context_t* zmq_context_;
  std::map<int, std::shared_ptr<zmq::socket_t>> senders_;
};

}  // namespace base
}  // namespace husky
