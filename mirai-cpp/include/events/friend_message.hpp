#pragma once
#ifndef mirai_cpp_events_friend_message_hpp_H_
#define mirai_cpp_events_friend_message_hpp_H_

#include <nlohmann/json.hpp>
#include "defs/qq_types.hpp"
#include "defs/message_chain.hpp"
#include "defs/friend.hpp"
#include "exported.h"
#include "event_interface.hpp"

namespace Cyan
{
	/**
	 * \brief 好友发来的消息
	 */
	class EXPORTED FriendMessage : public EventBase
	{
	public:
		Cyan::MessageChain MessageChain;
		Friend_t Sender;

		static MiraiEvent GetMiraiEvent()
		{
			return MiraiEvent::FriendMessage;
		}

		MessageId_t MessageId() const
		{
			return this->MessageChain.MessageId();
		}

		int64_t Timestamp() const
		{
			return this->MessageChain.Timestamp();
		}

		MessageId_t Reply(const Cyan::MessageChain& mc) const;
		MessageId_t QuoteReply(const Cyan::MessageChain& mc) const;

		virtual bool Set(const json& j) override
		{
			this->MessageChain.Set(j["messageChain"]);
			this->Sender.Set(j["sender"]);
			return true;
		}

		virtual json ToJson() const override
		{
			json j = json::object();
			j["messageChain"] = this->MessageChain.ToJson();
			j["sender"] = this->Sender.ToJson();
			return j;
		}
	};

}

#endif // !mirai_cpp_events_friend_message_hpp_H_