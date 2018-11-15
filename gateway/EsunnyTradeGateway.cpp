#include "TradeGateway.h"
#include "EsunnyTradeGateway.h"
#include <iTapTradeAPI.h>
#include <iTapAPIError.h>


namespace QCTech
{
	EsunnyTradeGateway::EsunnyTradeGateway(std::string gatewayName)
	{
		m_gatewayName = gatewayName;
	}
	EsunnyTradeGateway::~EsunnyTradeGateway()
	{
	
	}

	
	void EsunnyTradeGateway::LoadConfigure()
	{
		// TODO::�ӳ־û����ýӿ��ж�ȡ������Ϣ���־û����ýӿڿ��������ݿ�����������ļ�
		m_host = "61.163.243.173";
		m_port = 8383;

		strncpy_s(m_stAppInfo.AuthCode
			, "67EA896065459BECDFDB924B29CB7DF1946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE541DDE41BCBAB68D525B0D111A0884D847D57163FF7F329FA574E7946CED32E26C1EAC946CED32E26C1EAC733827B0CE853869ABD9B8F170E14F8847D3EA0BF4E191F5D97B3DFE4CCB1F01842DD2B3EA2F4B20CAD19B8347719B7E20EA1FA7A3D1BFEFF22290F4B5C43E6C520ED5A40EC1D50ACDF342F46A92CCF87AEE6D73542C42EC17818349C7DEDAB0E4DB16977714F873D505029E27B3D57EB92D5BEDA0A710197EB67F94BB1892B30F58A3F211D9C3B3839BE2D73FD08DD776B9188654853DDA57675EBB7D6FBBFC"
			, sizeof(m_stAppInfo.AuthCode));
		strncpy_s(m_stAppInfo.KeyOperationLogPath, "\\log", sizeof(m_stAppInfo.KeyOperationLogPath));
		
		strncpy_s(m_stLoginAuth.UserNo, "Q517608434", sizeof(m_stLoginAuth.UserNo));
		strncpy_s(m_stLoginAuth.Password, "302469", sizeof(m_stLoginAuth.Password));
		m_stLoginAuth.ISModifyPassword = APIYNFLAG_NO;
	}

	void EsunnyTradeGateway::Connect()
	{
		TAPIINT32 rtn = TAPIERROR_SUCCEED;
		LoadConfigure();

		std::cout << "��ʢ���׽ӿ�9.0��" << GetITapTradeAPIVersion() << "��" << std::endl;

		// ʵ����TradeAPI���׽ӿ�ʵ��
		m_pTradeApi = CreateITapTradeAPI(&m_stAppInfo, rtn);
		if (m_pTradeApi == nullptr)
		{
			std::cout << "����TradeAPIʵ��ʧ�ܡ������룺" << rtn << std::endl;
			return;
		}

		// ����API�Ļص��ӿڶ���
		rtn = m_pTradeApi->SetAPINotify(this);
		if (rtn != TAPIERROR_SUCCEED)
		{
			std::cout << "����API�Ļص��ӿڶ��󡣴����룺" << rtn << std::endl;
			return;
		}

		//�趨������IP���˿�
		rtn = m_pTradeApi->SetHostAddress(m_host.c_str(), m_port);
		if (rtn != TAPIERROR_SUCCEED)
		{
			std::cout << "���ӽ��׷�����ʧ�ܡ������룺" << rtn << std::endl;
			return;
		}

		//��¼������
		rtn = m_pTradeApi->Login(&m_stLoginAuth);
		if (rtn != TAPIERROR_SUCCEED) {
			std::cout << "��¼ʧ�ܡ�������:" << rtn << std::endl;
			return;
		}
		return;
	}

	void EsunnyTradeGateway::InsertOrder(StructInsertOrderReq & stOrderReq)
	{
		std::cout << __FUNCTION__ << std::endl;
		//m_pTradeApi->InsertOrder();
	}



#pragma region Spi interfaces in ITapTradeAPINotify
	/**
	* @brief ���ӳɹ��ص�֪ͨ
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnConnect()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	ϵͳ��¼���̻ص���
	* @details	�˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
	*			��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
	* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
	* @param[in] loginRspInfo ��½Ӧ����Ϣ�����errorCode!=0����loginRspInfo=NULL��
	* @attention	�ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ�
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	������֤��ϵ��ʽ֪ͨ��
	* @details	��¼��ɺ������Ҫ������֤��9.2.7��̨�������յ���ϵ��ʽ��֪ͨ������ѡ��֪ͨ��Ϣ��һ����ϵ��ʽ��������ߵ绰��
	*			�����Ͷ�����֤��Ȩ�루RequestVertificateCode����
	* @param[in] errorCode ���ش�����,0��ʾ�ɹ�������˻�û�а󶨶�����֤��ϵ��ʽ���򷵻�10016����
	* @param[in] isLast,��ʶ�Ƿ������һ����ϵ��Ϣ��
	* @param[in]  ��֤��ʽ��Ϣ�����errorCode!=0����ContactInfoΪ�ա�
	* @attention	�ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	�����Ͷ�����֤��Ӧ��
	* @details	�����ȡ������֤��Ȩ�룬��̨�����ʼ����߶��ţ�������Ӧ�𣬰�����������Լ���֤����Ч�ڡ�
	*
	* @param[in] sessionID ���������֤��ỰID��
	* @param[in]  errorCode ���û�а���ϵ������10016����.
	* @param[in]  rsp������֤����Ч�ڣ����뷵�أ��ڶ�����֤��Ч���ڣ������ظ����ö�����֤�룬���ǲ������������������֤�롣
	* @attention	�ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	API�������ѻص�
	* @details	�˺���ΪLogin()��¼�ɹ�������������뵱ǰ����С��30�죬����лص����ѡ�
	* @param[in] date ����API��Ȩ�����ա�
	* @param[in] days ���ػ��м�����Ȩ���ڡ�
	* @attention	�ú����ص�����˵����Ȩ��һ����֮�ڵ��ڡ����򲻲����ûص���
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	֪ͨ�û�API׼��������
	* @details	ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
	*			�˻ص�������API�ܷ����������ı�־��
	* @attention ������ſ��Խ��к�����������
	* @ingroup G_T_Login
	*/
	void TAP_CDECL EsunnyTradeGateway::OnAPIReady()
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	API�ͷ���ʧȥ���ӵĻص�
	* @details	��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
	* @param[in] reasonCode �Ͽ�ԭ����롣
	* @ingroup G_T_Disconnect
	*/
	void TAP_CDECL EsunnyTradeGateway::OnDisconnect(ITapTrade::TAPIINT32 reasonCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ֪ͨ�û������޸Ľ��
	* @param[in] sessionID �޸�����ĻỰID,��ChangePassword���صĻỰID��Ӧ��
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief ��֤�˻����뷴��
	* @param[in] sessionID �޸�����ĻỰID,��AuthPassword���صĻỰID��Ӧ��
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief �����û�Ԥ����Ϣ����
	* @param[in] sessionID �����û�Ԥ����Ϣ�ĻỰID
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @note �ýӿ���δʵ��
	* @ingroup G_T_UserInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	�����û���Ϣ
	* @details	�˻ص��ӿ����û����ز�ѯ���ʽ��˺ŵ���ϸ��Ϣ���û��б�Ҫ���õ����˺ű�ű���������Ȼ���ں����ĺ���������ʹ�á�
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief �����ʽ��˻����ʽ���Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	�û��ʽ�仯֪ͨ
	* @details	�û���ί�гɽ���������ʽ����ݵı仯�������Ҫ���û�ʵʱ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnFund(const ITapTrade::TapAPIFundData *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ����ϵͳ�еĽ�������Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeSystem
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	����ϵͳ��Ʒ����Ϣ
	* @details	�˻ص��ӿ��������û����صõ�������Ʒ����Ϣ��
	* @param[in] sessionID ����ĻỰID����GetAllCommodities()�������ض�Ӧ��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Commodity
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ����ϵͳ�к�Լ��Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Contract
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	����������Լ��Ϣ
	* @details	���û������µĺ�Լ����Ҫ���������ڽ���ʱ����з�����������º�Լʱ�����û����������Լ����Ϣ��
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Contract
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	��������Ӧ��
	* @details	�µ����������ĵ�Ӧ���µ������д�Ӧ��ص�������µ�����ṹ��û����д��Լ�����ʽ��˺ţ�������ش���š�
	* �������ĵ�������Ӧ���OnRtnOrder���ɹ�������OnRtnOrder�ص���
	* sessionID��ʶ�����Ӧ��sessionID���Ա�ȷ���ñ�Ӧ���Ӧ������
	*
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info ����Ӧ��������ͣ����������������ͺͶ�����Ϣָ�롣
	* ������Ϣָ�벿������¿���Ϊ�գ����Ϊ�գ�����ͨ��SessiuonID�ҵ���Ӧ�����ȡ�������͡�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ������ί�С����µĻ��������ط��µ����͹����ġ�
	* @details	���������յ��ͻ��µ�ί�����ݺ�ͻᱣ�������ȴ�������ͬʱ���û�����һ��
	*			��ί����Ϣ˵����������ȷ�������û������󣬷��ص���Ϣ�а�����ȫ����ί����Ϣ��
	*			ͬʱ��һ��������ʾ��ί�е�ί�кš�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	���ز�ѯ��ί����Ϣ
	* @details	�����û���ѯ��ί�еľ�����Ϣ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ���ز�ѯ��ί�б仯������Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����룬��errorCode==0ʱ��infoָ�򷵻ص�ί�б仯���̽ṹ�壬��ȻΪNULL��
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ���ص�ί�б仯����ָ�롣
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ���ز�ѯ�ĳɽ���Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	�������ĳɽ���Ϣ
	* @details	�û���ί�гɽ������û����ͳɽ���Ϣ��
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnFill(const ITapTrade::TapAPIFillInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ���ز�ѯ�ĳֲ�
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief �ֱֲ仯����֪ͨ
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ���ز�ѯ�ĳֲֻ���
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �ֲֻ��ܱ仯����֪ͨ
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPositionSummary(const TapAPIPositionSummary *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief �ֲ�ӯ��֪ͨ
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



	/**
	* @brief ����ϵͳ�еı�����Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeSystem
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief	������Ϣ֪ͨ
	* @details	���ز�ѯ���û��ʽ�״̬��Ϣ����Ϣ˵�����û����ʽ�״̬���û���Ҫ��ϸ�鿴��Щ��Ϣ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief	������Ϣ֪ͨ
	* @details	�û��ڽ��׹����п�����Ϊ�ʽ𡢳ֲ֡�ƽ�ֵ�״̬�䶯ʹ�˻�����ĳЩΣ��״̬������ĳЩ��Ҫ����Ϣ��Ҫ���û�֪ͨ��
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ʷί�в�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ʷί�����̲�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ʷ�ɽ���ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ʷ�ֲֲ�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ʷ�����ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief �ʽ������ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast 	��ʾ�Ƿ������һ������
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ѯ�û��˵�Ӧ�� Add:2013.12.11
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Bill
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ѯ�˻������Ѽ������ Add:2017.01.14
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Rent
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}

	/**
	* @brief ��ѯ�˻���֤�������� Add:2017.01.14
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Rent
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �۽���������˫�߱���Ӧ�� Add:2017.08.29
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �۽���������˫�߳���Ӧ�� Add:2017.08.29
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �۽���ѯ��֪ͨ Add:2017.08.29
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	void TAP_CDECL EsunnyTradeGateway::OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



	/**
	* @brief ����ɾ��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief ����¼��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �����޸�Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief ����ת��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief �ɽ�¼��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}


	/**
	* @brief ����ɾ��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	void TAP_CDECL EsunnyTradeGateway::OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info)
	{
		std::cout << __FUNCTION__ << std::endl;
	}



#pragma endregion

}