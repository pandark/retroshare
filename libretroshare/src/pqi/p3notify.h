#ifndef RS_P3_NOTIFY_INTERFACE_H
#define RS_P3_NOTIFY_INTERFACE_H

/*
 * libretroshare/src/rsserver: p3notify.h
 *
 * RetroShare C++ Interface.
 *
 * Copyright 2007-2008 by Robert Fernie.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License Version 2 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA.
 *
 * Please report all bugs and problems to "retroshare@lunamutt.com".
 *
 */

#include "retroshare/rsnotify.h"
#include "retroshare/rsturtle.h"

#include "util/rsthreads.h"

class p3NotifySysMsg
{
	public:

	uint32_t sysid;
	uint32_t type;
	std::string title;
	std::string msg;
};

class p3NotifyLogMsg
{
	public:

	uint32_t sysid;
	uint32_t type;
	std::string title;
	std::string msg;
};

class p3NotifyPopupMsg
{
	public:

	uint32_t type;
	std::string name;
        std::string title;
	std::string msg;
};


class p3Notify: public RsNotify
{
	public:

		p3Notify() : noteMtx("p3Notify") { return; }
		virtual ~p3Notify() { return; }

		virtual void registerNotifyClient(NotifyClient *nc) ;
        virtual bool unregisterNotifyClient(NotifyClient *nc) ;

		/* Pull output methods for retroshare-gui */
		virtual bool NotifySysMessage(uint32_t &sysid, uint32_t &type, std::string &title, std::string &msg);
		virtual bool NotifyPopupMessage(uint32_t &ptype, std::string &name, std::string &title, std::string &msg);
		virtual bool NotifyLogMessage(uint32_t &sysid, uint32_t &type, std::string &title, std::string &msg);

		virtual bool GetFeedItem(RsFeedItem &item);

		/* Control over Messages */
		bool GetSysMessageList(std::map<uint32_t, std::string> &list);
		bool GetPopupMessageList(std::map<uint32_t, std::string> &list);

		bool SetSysMessageMode(uint32_t sysid, uint32_t mode);
		bool SetPopupMessageMode(uint32_t ptype, uint32_t mode);

		/* Notify messages */
		bool AddPopupMessage(uint32_t ptype, const std::string& name, const std::string& title, const std::string& msg);
		bool AddSysMessage(uint32_t sysid, uint32_t type, const std::string& title, const std::string& msg);
		bool AddLogMessage(uint32_t sysid, uint32_t type, const std::string& title, const std::string& msg);
		bool AddFeedItem(uint32_t type, const std::string& id1, const std::string& id2 = "", const std::string& id3 = "", const std::string& id4 = "", uint32_t result1 = 0);
		bool ClearFeedItems(uint32_t type);

		// Notifications of clients. Can be called from anywhere inside libretroshare.
		//
		void notifyListPreChange              (int /* list */, int /* type */) ;
		void notifyListChange                 (int /* list */, int /* type */) ;
		void notifyErrorMsg                   (int /* list */, int /* sev  */, std::string /* msg */) ;
        void notifyChatMessage                (const ChatMessage& /* msg      */) ;
        void notifyChatStatus                 (const ChatId&      /* chat_id  */, const std::string& /* status_string */) ;
        void notifyChatLobbyEvent             (uint64_t           /* lobby id */, uint32_t           /* event type    */ , const RsGxsId & /* nickname */, const std::string& /* any string */) ;
		void notifyChatLobbyTimeShift         (int                /* time_shift*/) ;
		void notifyCustomState                (const std::string& /* peer_id   */, const std::string&               /* status_string */) ;
		void notifyHashingInfo                (uint32_t           /* type      */, const std::string&               /* fileinfo      */) ;
		void notifyTurtleSearchResult         (uint32_t           /* search_id */, const std::list<TurtleFileInfo>& /* files         */) ;
		void notifyPeerHasNewAvatar           (std::string        /* peer_id   */) ;
		void notifyOwnAvatarChanged           () ;
		void notifyOwnStatusMessageChanged    () ;
		void notifyDiskFull                   (uint32_t           /* location  */, uint32_t                         /* size limit in MB */) ;
		void notifyPeerStatusChanged          (const std::string& /* peer_id   */, uint32_t                         /* status           */) ;
        void notifyGxsChange                  (const RsGxsChanges& /* changes  */);

		void notifyPeerStatusChangedSummary   () ;
		void notifyDiscInfoChanged            () ;

		bool askForDeferredSelfSignature      (const void *       /* data      */, const uint32_t     /* len   */, unsigned char * /* sign */, unsigned int * /* signlen */,int& signature_result ) ;
		void notifyDownloadComplete           (const std::string& /* fileHash  */) ;
		void notifyDownloadCompleteCount      (uint32_t           /* count     */) ;
		void notifyHistoryChanged             (uint32_t           /* msgId     */, int /* type */) ;

        bool askForPassword                   (const std::string& /* key_details     */, bool               /* prev_is_bad */, std::string&, bool *cancelled /* password */ ) ;
		bool askForPluginConfirmation         (const std::string& /* plugin_filename */, const std::string& /* plugin_file_hash */) ;

	private:

		RsMutex noteMtx;

		std::list<p3NotifySysMsg> pendingSysMsgs;
		std::list<p3NotifyLogMsg> pendingLogMsgs;
		std::list<p3NotifyPopupMsg> pendingPopupMsgs;
		std::list<RsFeedItem>  pendingNewsFeed;

		std::list<NotifyClient*> notifyClients ;
};


#endif
