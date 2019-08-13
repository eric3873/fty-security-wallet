/*  =========================================================================
    fty_security_wallet_mlmagent - Security Wallet malamute agent

    Copyright (C) 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#ifndef FTY_SECURITY_WALLET_MLM_AGENT_H_INCLUDED
#define FTY_SECURITY_WALLET_MLM_AGENT_H_INCLUDED

#include "fty_common_mlm_agent.h"
#include "fty_security_wallet_classes.h"

#include <functional>

#include <cxxtools/serializationinfo.h>
/**
 * \brief Agent SecurityWalletMlmAgent main server actor
 */
namespace secw
{
    using Command   = std::string;
    using Sender    = std::string;
    using Subject   = std::string;


    class SecurityWalletServer;

    class SecurityWalletMlmAgent final : public mlm::MlmAgent
    {
    private:
        //attributs
        std::string m_storageconfigurationPath;
        std::string m_storageDatabasePath;
        std::string m_endpoint;
        std::shared_ptr<SecurityWalletServer> m_secwServer;


    public:
        explicit SecurityWalletMlmAgent(zsock_t *pipe);

    private:
        bool handleMailbox(zmsg_t *message) override;
        bool handlePipe(zmsg_t *message) override;
     
        //Notification function
        void publishOnBus(const std::string & payload);

        //Helpers
        static zmsg_t *generateErrorMsg(const std::string & correlationId, const std::string & errPayload);

    };


} // namespace secw

//  @interface
//  Create an fty_security_wallet_mlm_agent actor
FTY_SECURITY_WALLET_EXPORT void 
    fty_security_wallet_mlm_agent(zsock_t *pipe, void *endpoint);

//  Self test of this class
FTY_SECURITY_WALLET_EXPORT void
    fty_security_wallet_mlm_agent_test (bool verbose);

#endif



