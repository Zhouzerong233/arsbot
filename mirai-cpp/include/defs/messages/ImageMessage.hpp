#pragma once
#ifndef mirai_cpp_defs_messages_image_message_hpp_H_
#define mirai_cpp_defs_messages_image_message_hpp_H_

#include "defs/message_interface.hpp"
#include "defs/qq_types.hpp"

namespace Cyan
{
	class ImageMessage : public IMessage
	{
	public:
		ImageMessage() {}
		ImageMessage(const MiraiImage& m)
		{
			imageId_ = m.ID;
			url_ = m.Url;
			path_ = m.Path;
		}
		virtual const string& GetType() const override
		{
			return type_;
		}
		virtual bool operator==(const IMessage& m) const override
		{
			if (auto m_ptr = dynamic_cast<const ImageMessage*>(&m))
			{
				// �� ImageId ��Ϊ�ж����ݣ�������һ�� ImageId ��Ϊ��
				if (!m_ptr->imageId_.empty() || !this->imageId_.empty())
				{
					return (m_ptr->imageId_ == this->imageId_);
				}
				// ��� ImageId ��Ϊ�գ���ô�� url ���ж�һ��
				if (!m_ptr->url_.empty() || !this->url_.empty())
				{
					return (m_ptr->url_ == this->url_);
				}
				// ��� url ��Ϊ�գ���ô�� path ���ж�һ��
				if (!m_ptr->path_.empty() || !this->path_.empty())
				{
					return (m_ptr->path_ == this->path_);
				}
				// ����������Ϊ�գ������յ� ImageMessage ��Ȼ����ȵģ�
				return true;
			}
			// ���Ͷ���ͬ��ֱ�Ӳ���ȣ�
			return false;
		}
		virtual bool operator!=(const IMessage& m) const override
		{
			return !(*this == m);
		}
		virtual bool Set(const json& json) override
		{
			if (json["type"].is_null() || json["type"].get<string>() != this->GetType())
				throw std::runtime_error("������json����ȷ");
			if (!json["imageId"].is_null()) 
				imageId_ = json["imageId"].get<string>();
			if (!json["url"].is_null())
				url_ = json["url"].get<string>();
			if (!json["path"].is_null())
				path_ = json["path"].get<string>();
			return true;
		}
		virtual json ToJson() const override
		{
			return
			{
				{ "type", type_ },
				{ "imageId", imageId_ },
				{ "url", url_ },
				{ "path", path_ }
			};
		}
		virtual ~ImageMessage() {}

		MiraiImage ToMiraiImage() const
		{
			MiraiImage tmp;
			tmp.ID = imageId_;
			tmp.Url = url_;
			tmp.Path = path_;
			return tmp;
		}

	private:
		string type_ = "Image";
	protected:
		string imageId_;
		string url_;
		string path_;
	};

}
#endif

