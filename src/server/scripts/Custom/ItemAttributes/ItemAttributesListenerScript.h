/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ITEM_ATTRIBUTES_LISTENER_SCRIPT_H
#define _ITEM_ATTRIBUTES_LISTENER_SCRIPT_H

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "Warden.h"

class ItemAttributesListenerScript : public PlayerScript
{
public:
    ItemAttributesListenerScript() : PlayerScript("ItemAttributesListenerScript") { }

private:
    std::vector<std::string> Split(const std::string& s, char delimiter);
    std::vector<std::string> GetChunks(std::string s, uint8_t chunkSize);
    void SendChunkedPayload(Warden* warden, WardenPayloadMgr* payloadMgr, std::string payload, uint32 chunkSize);

    void OnLogin(Player* player) override;
    void OnLogout(Player* player) override;
    void OnBeforeSendChatMessage(Player* player, uint32& type, uint32& lang, std::string& msg) override;

private:
    const std::string _listenerPayload = "local a=CreateFrame('Frame')a:RegisterEvent('CHAT_MSG_ADDON')a:SetScript('OnEvent',function(self,b,...)local c,d,e,f=...if b=='CHAT_MSG_ADDON'and c=='wlrx'and e=='WHISPER'and f==UnitName('player')then forceinsecure()loadstring(d)()end end)function SendReload()SendAddonMessage('wltx','reload','WHISPER',UnitName('player'))end;SlashCmdList['RELOAD']=function()ReloadUI()SendReload()end;local g=RestartGx;RestartGx=function()g()SendReload()end";
    const uint16 _prePayloadId = 9600;
    const uint16 _postPayloadId = 9601;
    const uint16 _tmpPayloadId = 9602;
    const std::string _prePayload = "wlbuf = '';";
    const std::string _postPayload = "local a,b=loadstring(wlbuf)if not a then message(b)else a()end";
};

#endif
