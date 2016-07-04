//	Copyright (c) 2016, TecSec, Inc.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//	
//		* Redistributions of source code must retain the above copyright
//		  notice, this list of conditions and the following disclaimer.
//		* Redistributions in binary form must reproduce the above copyright
//		  notice, this list of conditions and the following disclaimer in the
//		  documentation and/or other materials provided with the distribution.
//		* Neither the name of TecSec nor the names of the contributors may be
//		  used to endorse or promote products derived from this software 
//		  without specific prior written permission.
//		 
//	ALTERNATIVELY, provided that this notice is retained in full, this product
//	may be distributed under the terms of the GNU General Public License (GPL),
//	in which case the provisions of the GPL apply INSTEAD OF those given above.
//		 
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED.  IN NO EVENT SHALL TECSEC BE LIABLE FOR ANY 
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Written by Roger Butler

#include "stdafx.h"

using namespace tscrypto;

static SSL_CIPHER gCkmAuthAlgs[] = {
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_256_CCM_SHA384,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_128_CCM_SHA256,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_256_CCM_8_SHA384,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_128_CCM_8_SHA256,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_256_CBC_SHA384,
	_SSL_CIPHER::TLS_CKMAUTH_WITH_AES_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_256_GCM_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_128_GCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_256_CCM_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_128_CCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_256_CCM_8_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_128_CCM_8_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_ARIA_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_256_GCM_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_128_GCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_256_CCM_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_128_CCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_256_CCM_8_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_128_CCM_8_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_CAMELLIA_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_CKMAUTH_WITH_SEED_128_GCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_SEED_128_CCM_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_SEED_128_CCM_8_SHA256,
	//_SSL_CIPHER::TLS_CKMAUTH_WITH_SEED_128_CBC_SHA256,
};

static SSL_CIPHER gSupportedPkCiphers[] =
{
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_CHACHA20_POLY1305_SHA256,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_128_CCM,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_256_CCM,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8,

	//_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,

	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256,

	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_CHACHA20_POLY1305_SHA256,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,

	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA,

	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384,
	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256,

	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256,

	//_SSL_CIPHER::TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384,
	//_SSL_CIPHER::TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256,

	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384,
	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256,
	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_ECDH_RSA_WITH_AES_128_CBC_SHA,

	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA,

	_SSL_CIPHER::TLS_RSA_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_RSA_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_RSA_WITH_AES_128_CCM,
	_SSL_CIPHER::TLS_RSA_WITH_AES_256_CCM,
	_SSL_CIPHER::TLS_RSA_WITH_AES_128_CCM_8,
	_SSL_CIPHER::TLS_RSA_WITH_AES_256_CCM_8,

	_SSL_CIPHER::TLS_RSA_WITH_AES_256_CBC_SHA256,
	_SSL_CIPHER::TLS_RSA_WITH_AES_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256         ,
	//_SSL_CIPHER::TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256         ,

	_SSL_CIPHER::TLS_RSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_RSA_WITH_AES_128_CBC_SHA,

	//_SSL_CIPHER::TLS_RSA_WITH_CAMELLIA_256_CBC_SHA,
	//_SSL_CIPHER::TLS_RSA_WITH_CAMELLIA_128_CBC_SHA,

	//_SSL_CIPHER::TLS_RSA_WITH_SEED_CBC_SHA,


	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_256_GCM_SHA384          ,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_128_GCM_SHA256          ,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_256_CBC_SHA256          ,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_128_CBC_SHA256          ,

	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256,
	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256,

	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384,
	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256,

	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_128_CBC_SHA,
	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA        ,
	//_SSL_CIPHER::TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA        ,
	//_SSL_CIPHER::TLS_DHE_RSA_WITH_SEED_CBC_SHA                ,


	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_256_GCM_SHA384           ,
	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_128_GCM_SHA256           ,

	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_256_CCM,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_128_CCM,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_256_CCM_8,
	_SSL_CIPHER::TLS_DHE_RSA_WITH_AES_128_CCM_8,

	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_256_CBC_SHA256           ,
	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_128_CBC_SHA256           ,
	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_256_CBC_SHA              ,
	_SSL_CIPHER::TLS_DH_RSA_WITH_AES_128_CBC_SHA              ,

	//_SSL_CIPHER::TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA256,
	//_SSL_CIPHER::TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA256,
	//_SSL_CIPHER::TLS_DH_RSA_WITH_CAMELLIA_256_CBC_SHA         ,
	//_SSL_CIPHER::TLS_DH_RSA_WITH_CAMELLIA_128_CBC_SHA         ,

	//_SSL_CIPHER::TLS_DH_RSA_WITH_SEED_CBC_SHA                 ,

	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_256_GCM_SHA384,
	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_128_GCM_SHA256,
	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_256_CBC_SHA256,
	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_128_CBC_SHA256,
	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_256_CBC_SHA,
	_SSL_CIPHER::TLS_DHE_DSS_WITH_AES_128_CBC_SHA,

	//_SSL_CIPHER::TLS_DHE_DSS_WITH_CAMELLIA_256_CBC_SHA,
	//_SSL_CIPHER::TLS_DHE_DSS_WITH_CAMELLIA_128_CBC_SHA,

	//_SSL_CIPHER::TLS_DHE_DSS_WITH_SEED_CBC_SHA,

	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_256_GCM_SHA384           ,
	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_128_GCM_SHA256           ,
	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_256_CBC_SHA256           ,
	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_128_CBC_SHA256           ,
	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_256_CBC_SHA              ,
	_SSL_CIPHER::TLS_DH_DSS_WITH_AES_128_CBC_SHA              ,

	//_SSL_CIPHER::TLS_DH_DSS_WITH_CAMELLIA_256_CBC_SHA         ,
	//_SSL_CIPHER::TLS_DH_DSS_WITH_CAMELLIA_128_CBC_SHA         ,
	//
	//_SSL_CIPHER::TLS_DH_DSS_WITH_SEED_CBC_SHA                 ,
};

class TcpMsgProcessor : public IMessageProcessorControl, public IHttpChannelProcessor, public authenticationInitiatorTunnelKeyHandler, public authenticationControlDataCommunications, public tsmod::IObject
{
public:
	virtual bool WrapMessage(tscrypto::tsCryptoString& verb, tscrypto::tsCryptoString& destination, tscrypto::tsCryptoData &body, tscrypto::tsCryptoString& mimeType, HttpAttributeList headers)
	{
		MY_UNREFERENCED_PARAMETER(headers);

		tscrypto::tsCryptoString origUrl(destination);
		JSONObject bodyObj;
		JSONObject requestData;
		int tmp;
		tscrypto::tsCryptoData msgNo;
		tscrypto::tsCryptoData tag;
		tscrypto::tsCryptoData _msgIv1;
		tscrypto::tsCryptoData _msgMac1;

		UrlParser parser, parser2;

		parser.ParseFullUrl(destination);
		if (parser.getPath().size() > 0 && parser.getPath()[0] != '/')
			parser.setPath("/" + parser.getPath());

		if (verb == "GET" && body.size() > 0 && bodyObj.FromJSON(body.ToUtf8String().c_str()))
		{
			bodyObj.foreach([&parser, this](const JSONField& fld) {
				NameValue nv;

				nv.name = fld.Name();
				nv.value = fld.AsString();
				parser.getParameters()->push_back(nv);
			});
			body.clear();
		}

		parser2.setPath(parser.getFile());
		parser2.setParameters(parser.getParameters());
		parser2.setHash(parser.getHash());


		requestData.add("u", parser2.BuildUrl()).add("v", verb).add("m", mimeType);

		if (body.size() > 0)
			requestData.add("p", body.ToBase64());
		body.clear();

		tmp = tscrypto::XP_ntohl(_sequenceNumber);

		msgNo.assign((uint8_t*)&tmp, sizeof(int));

		body = requestData.ToJSON().ToUTF8Data().ToBase64();

		if (!!_AEAD)
		{
			if (!SP800_108_Counter(_sessionKey, _sessionId, msgNo, 448, _msgKey))
			{
				return false;
			}

			_msgIv1 = _msgKey.substring(32, 12);
			_msgIv2 = _msgKey.substring(44, 12);
			_msgKey.erase(32, 24);
			if (!_AEAD->initialize(_msgKey) || !_AEAD->encryptMessage(_msgIv1, tscrypto::tsCryptoData(), body, 16, tag))
				return false;
			//if (!GCM_Encrypt(_msgKey, _msgIv1, tscrypto::tsCryptoData(), body, tag))
			//	return false;
		}
		else if (!!_symm)
		{
			int keySize = (int)_symm->currentKeySizeInBits();
			int ivSize = (int)_symm->getIVECSizeForMode(_symm->getCurrentMode()) * 8;
			int macKeySize = 0;
			tscrypto::tsCryptoData finalBlock;

			if (!!_MAC)
				macKeySize = keySize;

			if (!SP800_108_Counter(_sessionKey, _sessionId, msgNo, keySize + 2 * ivSize + 2 * macKeySize, _msgKey))
			{
				return false;
			}

			if (ivSize > 0)
			{
				_msgIv1 = _msgKey.substring(keySize / 8, ivSize / 8);
				_msgIv2 = _msgKey.substring((keySize + ivSize) / 8, ivSize / 8);
			}
			if (macKeySize > 0)
			{
				_msgMac1 = _msgKey.substring((keySize + 2 * ivSize) / 8, macKeySize / 8);
				_msgMac2 = _msgKey.substring((keySize + 2 * ivSize + macKeySize) / 8, macKeySize / 8);
			}
			_msgKey.resize(keySize / 8);
			if (!!_hasher)
			{
				if (!_hasher->initialize() || !_hasher->update(body) || !_hasher->finish(tag))
					return false;
			}
			else if (!!_MAC)
			{
				if (!_MAC->initialize(_msgMac1) || !_MAC->update(body) || !_MAC->finish(tag))
					return false;
			}

			_symm->setPaddingType(_SymmetricPaddingType::padding_Pkcs5);
			if (!_symm->init(true, _symm->getCurrentMode(), _msgKey, _msgIv1) || !_symm->update(body, body) || !_symm->finish(finalBlock))
				return false;
			body += finalBlock;
		}
		else
			return false;

		requestData.clear();
		requestData
			.add("d", body.ToBase64())
			.add("t", tag.ToBase64())
			.add("s", _sessionId.ToBase64())
			.add("i", (int64_t)(_sequenceNumber++));

		body = requestData.ToJSON().ToUTF8Data();
		mimeType = "application/vnd.tecsec.ckmauthtunnel+json";
		verb = "POST";

		parser.getParameters()->clear();
		parser.setHash("");
		parser.RemoveFileFromPath();
		parser.AppendToPath("portal");
		destination = parser.BuildUrl();
		return true;
	}
	virtual bool UnwrapMessage(IHttpResponse* header)
	{
		if (header->dataPartSize() > 0 && _msgKey.size() > 0 && _msgIv2.size() > 0)
		{
			JSONObject data;
			tscrypto::tsCryptoData body;

			if (!data.FromJSON(header->dataPart().ToUtf8String().c_str()))
			{
				return false;
			}
			if (data.AsString("s") != _sessionId.ToBase64() || data.AsNumber("i", 0) != _sequenceNumber - 1)
				return false;

			body = data.AsString("d").Base64ToData();

			if (!!_AEAD)
			{
				if (!_AEAD->initialize(_msgKey) || !_AEAD->decryptMessage(_msgIv2, tscrypto::tsCryptoData(), body, data.AsString("t").Base64ToData()))
					return false;
				//if (!GCM_Decrypt(_msgKey, _msgIv2, tscrypto::tsCryptoData(), body, data.AsString("t").Base64ToData()))
				//	return false;
			}
			else if (!!_symm)
			{
				tscrypto::tsCryptoData finalBlock;
				tscrypto::tsCryptoData tag;

				if (!!_hasher)
				{
					if (!_hasher->initialize() || !_hasher->update(body) || !_hasher->finish(tag) || tag != data.AsString("t").Base64ToData())
						return false;
				}
				else if (!!_MAC)
				{
					if (!_MAC->initialize(_msgMac2) || !_MAC->update(body) || !_MAC->finish(tag) || tag != data.AsString("t").Base64ToData())
						return false;
				}

				_symm->setPaddingType(_SymmetricPaddingType::padding_Pkcs5);
				if (!_symm->init(false, _symm->getCurrentMode(), _msgKey, _msgIv2) || !_symm->update(body, body) || !_symm->finish(finalBlock))
					return false;
				body += finalBlock;
			}
			else
				return false;

			_msgKey.clear();
			_msgIv2.clear();

			data.clear();
			if (!data.FromJSON(body.ToUtf8String().c_str()))
				return false;
			header->errorCode((WORD)data.AsNumber("c", 0));
			body = data.AsString("p").Base64ToData();
			header->dataPart(body);
		}
		return true;
	}

	virtual void ClearTlsCipherList() override
	{
		_ciphers.clear();
	}
	virtual void SetCipherList(SSL_CIPHER* list, size_t count) override
	{
		ClearTlsCipherList();
		for (size_t i = 0; i < count; i++)
		{
			_ciphers.push_back(list[i]);
		}
	}
	virtual void AddCipher(SSL_CIPHER cipher) override
	{
		_ciphers.push_back(cipher);
	}
	void RegisterCertificateVerifier(std::function<SSL_AlertDescription(const tscrypto::tsCryptoDataList& certificate, SSL_CIPHER cipher)> func) override
	{
		_CertVerifier = func;
	}
	virtual tscrypto::tsCryptoString CkmAuthUsername() const override
	{
		return _ckmAuthUsername;
	}
	virtual void CkmAuthUsername(const tscrypto::tsCryptoString& setTo) override
	{
		_ckmAuthUsername = setTo;
	}
	virtual void RegisterPSKCallback(std::function<bool(const tscrypto::tsCryptoData& hint, tscrypto::tsCryptoData& identity, tscrypto::tsCryptoData& psk)> func) override
	{
		_pskCallback = func;
	}

	virtual bool WrapTransport(tscrypto::tsCryptoData& content) override
	{
		if (!!_httpsTunnel)
		{
			if (_state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolClosed || _state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolReset)
				return false;
			if (!_httpsTunnel->SendData(content))
				return false;
			content.clear();
			return true;
		}
		if (!!_tunnel)
		{
			tscrypto::tsCryptoData src(content);
			return _tunnel->SendData(src, content);
		}
		return true;
	}
	virtual bool UnwrapTransport(tscrypto::tsCryptoData& content) override
	{
		if (!!_httpsTunnel)
		{
			if (_state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolClosed || _state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolReset)
				return false;

			return _httpsTunnel->ProcessCommsData(content);
		}
		if (!!_tunnel)
		{
			tscrypto::tsCryptoData src(content);
			return _tunnel->ReceiveData(src, content);
		}
		return true;
	}
	virtual bool Logout() override
	{
		_serverPin.clear();
		if (!!_httpsTunnel)
		{
			_httpsTunnel->Logout();
			_sessionId.clear();
			_sessionKey.clear();
			_AEAD.reset();
			_symm.reset();
			_hasher.reset();
			return _httpsTunnel->Close();
		}
		if (!!_tunnel)
			return _tunnel->Logout();
		return false;
	}
	virtual TransportState GetTransportState() override
	{
		if (!!_httpsTunnel)
		{
			switch (_state)
			{
			case _SSL_CONNECTION_STATE::ssl_conn_Hello_Request:
			case _SSL_CONNECTION_STATE::ssl_conn_Logout:
				return logout;
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Hello:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Hello:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Certificate:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Key_Exchange:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Hello_Done:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Certificate_Request:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Key_Exchange:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Certificate:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Certificate_Verify:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Send_Change_Cipher_Spec:
			case _SSL_CONNECTION_STATE::ssl_conn_Client_Finished:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Send_Change_Cipher_Spec:
			case _SSL_CONNECTION_STATE::ssl_conn_Server_Finished:
				return login;
			case _SSL_CONNECTION_STATE::ssl_conn_Active:
				return active;
			case _SSL_CONNECTION_STATE::ssl_conn_ProtocolReset:
			case _SSL_CONNECTION_STATE::ssl_conn_ProtocolClosed:
			default:
				return inactive;
			}
		}
		return _transportState;
	}
	virtual bool isAuthenticated() const override
	{
		if ((!!_httpsTunnel && _httpsTunnel->isValid()))
			return true;
		return (!!_tunnel && _tunnel->TunnelActive()) || _sessionKey.size() > 0;
	}

	// IMessageProcessorControl
	virtual void clear() override
	{
		_serverPin.clear();
		_msgIv2.clear();
		_msgMac2.clear();
		_msgKey.clear();
		_sessionKey.clear();
		_sequenceNumber = 0;
		_sessionId.clear();
		_username.clear();
		_channel.reset();
		_AEAD.reset();
		_symm.reset();
		_hasher.reset();
		if (!!_httpsTunnel)
			_httpsTunnel->Reset();
		_transportState = IHttpChannelProcessor::inactive;
	}
	virtual void start(const tscrypto::tsCryptoData& sessionId, const tscrypto::tsCryptoData& sessionKey) override
	{
		clear();
		_sessionId = sessionId;
		_sessionKey = sessionKey;
		_AEAD = std::dynamic_pointer_cast<CCM_GCM>(CryptoFactory("GCM-AES"));
	}

	virtual bool startTunnel(const tscrypto::tsCryptoString& scheme, std::shared_ptr<ITcpChannel> channel, const tscrypto::tsCryptoString& username, const tscrypto::tsCryptoData& password) override
	{
		_channel = channel;
		_username = username;
		_serverPin = password;

		if (TsStriCmp(scheme, "https") == 0)
		{
			if (!(_httpsTunnel = ::TopServiceLocator()->get_instance<ISslHandshake_Client>("PROTOCOL_SSL_CLIENT")))
				return false;
			_httpsTunnel->useCompression(false);
			_httpsTunnel->RegisterCommsDataSendCallback([this](const tscrypto::tsCryptoData& data)->bool { return sendControlData(data); });
			_httpsTunnel->RegisterStateChangeCallback([this](SSL_CONNECTION_STATE state) { stateChanged(state); });
			_httpsTunnel->RegisterCertificateVerifier([this](const tscrypto::tsCryptoDataList& certificate, SSL_CIPHER cipher) { return CertificateVerifier(certificate, cipher); });
			if (_ciphers.size() > 0)
				_httpsTunnel->setCiphersSupported(_ciphers.data(), _ciphers.size());
			else
			{
				std::vector<SSL_CIPHER> ciphers;

				if (username.size() > 0 && password.size() > 0)
				{
					ciphers.reserve(ciphers.size() + (sizeof(gCkmAuthAlgs) / sizeof(gCkmAuthAlgs[0])));
					for (SSL_CIPHER cipher : gCkmAuthAlgs)
					{
						ciphers.push_back(cipher);
					}
				}
				else
				{
					ciphers.reserve(ciphers.size() + (sizeof(gSupportedPkCiphers) / sizeof(gSupportedPkCiphers[0])));
					for (SSL_CIPHER cipher : gSupportedPkCiphers)
					{
						ciphers.push_back(cipher);
					}
				}
				_httpsTunnel->setCiphersSupported(ciphers.data(), ciphers.size());
			}
			if (!!_pskCallback)
				_httpsTunnel->RegisterClientPSK(_pskCallback);
			_httpsTunnel->RegisterPasswordCallback([this](tscrypto::tsCryptoData& password) { password = _serverPin; return true; });
			_httpsTunnel->setCkmAuthUsername(_username);
			_httpsTunnel->RegisterMessageKeyCallback([this](const tscrypto::tsCryptoData& key, const tscrypto::AlgorithmIdentifier& encAlg, const tscrypto::AlgorithmIdentifier& macAlg) { return messageKeyCallback(key, encAlg, macAlg); });
			if (!_httpsTunnel->Connect())
				return false;
			return true;
		}
		else if (TsStriCmp(scheme, "httpv") == 0 || TsStriCmp(scheme, "ckm-http") == 0)
		{
			_transportState = IHttpChannelProcessor::login;
			if (!(_tunnel = std::dynamic_pointer_cast<CkmAuthenticationTunnelInitiator>(CryptoFactory("TUNNEL-INITIATOR"))))
				return false;
			if (!_tunnel->StartTunnel(username.c_str(), this, this))
				return false;
			return true;
		}
		else
			return false;
	}

	// authenticationInitiatorTunnelKeyHandler
	virtual tscrypto::tsCryptoData getAuthenticationInformation(const tscrypto::tsCryptoData& serverRequirements) override
	{
		CkmAuthInitiatorParameters initParams;
		tscrypto::tsCryptoString password;

		if (!initParams.Decode(serverRequirements))
		{
			return tscrypto::tsCryptoData();
		}

		if (initParams._authParameters._params.selectedItem != CkmAuthServerParameters_params::Choice_Pbkdf)
		{
			return tscrypto::tsCryptoData();
		}
		return _serverPin;
	}

	// authenticationControlDataCommunications
	virtual bool sendControlData(const tscrypto::tsCryptoData& dest) override
	{
		if (!!_channel)
			return _channel->RawSend(dest);
		return false;
	}
	virtual void stateChanged(bool isActive) override
	{
		if (isActive)
		{
			_transportState = IHttpChannelProcessor::active;
			if (!_tunnel->GetMessageAuth(_sessionKey))
				_sessionKey.clear();
			if (_sessionKey.size() > 32)
			{
				_sessionId = _sessionKey.substring(32, _sessionKey.size() - 32);
				_sessionKey.resize(32);
				_sequenceNumber = 0;

				AlgorithmIdentifier encAlg;
				AlgorithmIdentifier macAlg;

				if (!_tunnel->GetMessageEncryptionAlg(encAlg) || !_tunnel->GetMessageHashAlg(macAlg))
				{
					return;
				}

				_AEAD.reset();
				_symm.reset();
				_hasher.reset();
				_MAC.reset();

				// Use the alg parameter to specify the encryption alg for the message data
				if (encAlg._oid.oid().size() > 0)
				{
					std::shared_ptr<tscrypto::IObject> obj = CryptoFactory(encAlg._oid.oidString());
					_AEAD = std::dynamic_pointer_cast<CCM_GCM>(obj);
					_symm = std::dynamic_pointer_cast<Symmetric>(obj);

					if (!!_symm)
					{
						if (macAlg._oid.oid().size() > 0)
						{
							obj.reset();
							obj = CryptoFactory(macAlg._oid.oidString());
							_hasher = std::dynamic_pointer_cast<Hash>(obj);
							_MAC = std::dynamic_pointer_cast<MAC>(obj);
						}
					}
				}
				else
				{
					_AEAD = std::dynamic_pointer_cast<CCM_GCM>(CryptoFactory("GCM-AES"));
				}


			}
		}
		else
		{
			_AEAD.reset();
			_symm.reset();
			_hasher.reset();
			_MAC.reset();

			_transportState = IHttpChannelProcessor::logout;
			_sessionId.clear();
			_sessionKey.clear();
		}
	}
	virtual void failed(const char *message) override
	{
		//LOG(gHttpLog, "CHANNEL ERROR:  " << message);
		_failureReason = message;
	}
	virtual void loggedOut() override
	{
		_username.clear();
		_serverPin.clear();
		_sessionKey.clear();
		_sessionId.clear();
		_sequenceNumber = 0;
	}
	virtual tscrypto::tsCryptoString failureReason() const override
	{
		return _failureReason;
	}

	TcpMsgProcessor() : _transportState(IHttpChannelProcessor::inactive), _sequenceNumber(0) {}
	~TcpMsgProcessor(){}
protected:
	SSL_AlertDescription CertificateVerifier(const tscrypto::tsCryptoDataList& certificate, SSL_CIPHER cipher)
	{
		if (!!_CertVerifier)
		{
			return _CertVerifier(certificate, cipher);
		}
		// TODO:  Implement default cert verifier here


		return _SSL_AlertDescription::sslalert_no_error;
	}
	virtual void stateChanged(SSL_CONNECTION_STATE state)
	{
		_state = state;
		if (state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolReset || state == _SSL_CONNECTION_STATE::ssl_conn_ProtocolClosed)
		{
			if (!!_channel)
				_channel->setChannelProcessor(nullptr);
			clear();
			//if (!!_channel)
			//	_channel->Disconnect();
		}
	}
	bool messageKeyCallback(const tscrypto::tsCryptoData& key, const tscrypto::AlgorithmIdentifier& encAlg, const tscrypto::AlgorithmIdentifier& macAlg)
	{
		_sessionId = key.substring(32, key.size() - 32);
		_sessionKey = key.substring(0, 32);

		_AEAD.reset();
		_symm.reset();
		_hasher.reset();
		_MAC.reset();

		// Use the alg parameter to specify the encryption alg for the message data
		if (encAlg._oid.oid().size() > 0)
		{
			std::shared_ptr<tscrypto::IObject> obj = CryptoFactory(encAlg._oid.oidString());
			_AEAD = std::dynamic_pointer_cast<CCM_GCM>(obj);
			_symm = std::dynamic_pointer_cast<Symmetric>(obj);
			
			if (!!_symm)
			{
				if (macAlg._oid.oid().size() > 0)
				{
					obj.reset();
					obj = CryptoFactory(macAlg._oid.oidString());
					_hasher = std::dynamic_pointer_cast<Hash>(obj);
					_MAC = std::dynamic_pointer_cast<MAC>(obj);
				}
			}
		}
		else
		{
			_AEAD = std::dynamic_pointer_cast<CCM_GCM>(CryptoFactory("GCM-AES"));
		}
		return true;
	}
protected:
	tscrypto::tsCryptoData _msgIv2;
	tscrypto::tsCryptoData _msgMac2;
	tscrypto::tsCryptoData _msgKey;
	tscrypto::tsCryptoData _sessionKey;
	int _sequenceNumber;
	tscrypto::tsCryptoData _sessionId;
	tscrypto::tsCryptoString _username;
	tscrypto::tsCryptoData _serverPin;
	std::shared_ptr<CkmAuthenticationTunnelInitiator> _tunnel;
	std::shared_ptr<ITcpChannel> _channel;
	IHttpChannelProcessor::TransportState _transportState;
	// SSL variables
	std::shared_ptr<ISslHandshake_Client> _httpsTunnel;
	SSL_CONNECTION_STATE _state;
	std::vector<SSL_CIPHER> _ciphers;
	std::function<SSL_AlertDescription(const tscrypto::tsCryptoDataList& certificate, SSL_CIPHER cipher)> _CertVerifier;
	std::function<bool(const tscrypto::tsCryptoData& hint, tscrypto::tsCryptoData& identity, tscrypto::tsCryptoData& psk)> _pskCallback;
	tscrypto::tsCryptoString _ckmAuthUsername;

	std::shared_ptr<CCM_GCM> _AEAD;
	std::shared_ptr<Symmetric> _symm;
	std::shared_ptr<Hash> _hasher;
	std::shared_ptr<MAC> _MAC;

	tscrypto::tsCryptoString _failureReason;
};


tsmod::IObject* CreateTcpMsgProcessor()
{
	return dynamic_cast<tsmod::IObject*>(new TcpMsgProcessor());
}
