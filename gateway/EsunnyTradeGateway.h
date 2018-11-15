#pragma once
#include <iostream>
#include <iTapTradeAPI.h>
#include "TradeGateway.h"


namespace QCTech
{
	using namespace ITapTrade;

	class EsunnyTradeGateway : public TradeGateway, protected ITapTradeAPINotify
	{
	public:
		EsunnyTradeGateway(std::string gatewayName = "Esunny");
		virtual ~EsunnyTradeGateway();
	
	public:
		virtual void LoadConfigure();
		virtual void Connect();
		virtual void InsertOrder(StructInsertOrderReq& stOrderReq);

	public:
#pragma region Spi interfaces in ITapTradeAPINotify
		/**
		* @brief ���ӳɹ��ص�֪ͨ
		* @ingroup G_T_Login
		*/
		virtual void TAP_CDECL OnConnect();
		/**
		* @brief	ϵͳ��¼���̻ص���
		* @details	�˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
		*			��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
		* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
		* @param[in] loginRspInfo ��½Ӧ����Ϣ�����errorCode!=0����loginRspInfo=NULL��
		* @attention	�ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ�
		* @ingroup G_T_Login
		*/
		virtual void TAP_CDECL OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo);
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
		virtual void TAP_CDECL OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo);

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
		virtual void TAP_CDECL OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const TapAPIRequestVertificateCodeRsp *rsp);

		/**
		* @brief	API�������ѻص�
		* @details	�˺���ΪLogin()��¼�ɹ�������������뵱ǰ����С��30�죬����лص����ѡ�
		* @param[in] date ����API��Ȩ�����ա�
		* @param[in] days ���ػ��м�����Ȩ���ڡ�
		* @attention	�ú����ص�����˵����Ȩ��һ����֮�ڵ��ڡ����򲻲����ûص���
		* @ingroup G_T_Login
		*/
		virtual void TAP_CDECL OnExpriationDate(ITapTrade::TAPIDATE date, int days);

		/**
		* @brief	֪ͨ�û�API׼��������
		* @details	ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
		*			�˻ص�������API�ܷ����������ı�־��
		* @attention ������ſ��Խ��к�����������
		* @ingroup G_T_Login
		*/
		virtual void TAP_CDECL OnAPIReady();
		/**
		* @brief	API�ͷ���ʧȥ���ӵĻص�
		* @details	��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
		* @param[in] reasonCode �Ͽ�ԭ����롣
		* @ingroup G_T_Disconnect
		*/
		virtual void TAP_CDECL OnDisconnect(ITapTrade::TAPIINT32 reasonCode);
		/**
		* @brief ֪ͨ�û������޸Ľ��
		* @param[in] sessionID �޸�����ĻỰID,��ChangePassword���صĻỰID��Ӧ��
		* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
		* @ingroup G_T_UserInfo
		*/
		virtual void TAP_CDECL OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);

		/**
		* @brief ��֤�˻����뷴��
		* @param[in] sessionID �޸�����ĻỰID,��AuthPassword���صĻỰID��Ӧ��
		* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
		* @ingroup G_T_UserInfo
		*/
		virtual void TAP_CDECL OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
		/**
		* @brief �����û�Ԥ����Ϣ����
		* @param[in] sessionID �����û�Ԥ����Ϣ�ĻỰID
		* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
		* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @note �ýӿ���δʵ��
		* @ingroup G_T_UserInfo
		*/
		virtual void TAP_CDECL OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info);
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
		virtual void TAP_CDECL OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info);
		/**
		* @brief �����ʽ��˻����ʽ���Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_AccountDetails
		*/
		virtual void TAP_CDECL OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info);
		/**
		* @brief	�û��ʽ�仯֪ͨ
		* @details	�û���ί�гɽ���������ʽ����ݵı仯�������Ҫ���û�ʵʱ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_AccountDetails
		*/
		virtual void TAP_CDECL OnRtnFund(const ITapTrade::TapAPIFundData *info);
		/**
		* @brief ����ϵͳ�еĽ�������Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeSystem
		*/
		virtual void TAP_CDECL OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info);
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
		virtual void TAP_CDECL OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info);
		/**
		* @brief ����ϵͳ�к�Լ��Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_Contract
		*/
		virtual void TAP_CDECL OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info);
		/**
		* @brief	����������Լ��Ϣ
		* @details	���û������µĺ�Լ����Ҫ���������ڽ���ʱ����з�����������º�Լʱ�����û����������Լ����Ϣ��
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_Contract
		*/
		virtual void TAP_CDECL OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info);
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
		virtual void TAP_CDECL OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info);
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
		virtual void TAP_CDECL OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info);
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
		virtual void TAP_CDECL OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
		/**
		* @brief ���ز�ѯ��ί�б仯������Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����룬��errorCode==0ʱ��infoָ�򷵻ص�ί�б仯���̽ṹ�壬��ȻΪNULL��
		* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info ���ص�ί�б仯����ָ�롣
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeInfo
		*/
		virtual void TAP_CDECL OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
		/**
		* @brief ���ز�ѯ�ĳɽ���Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeInfo
		*/
		virtual void TAP_CDECL OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info);
		/**
		* @brief	�������ĳɽ���Ϣ
		* @details	�û���ί�гɽ������û����ͳɽ���Ϣ��
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeActions
		*/
		virtual void TAP_CDECL OnRtnFill(const ITapTrade::TapAPIFillInfo *info);
		/**
		* @brief ���ز�ѯ�ĳֲ�
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeInfo
		*/
		virtual void TAP_CDECL OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info);
		/**
		* @brief �ֱֲ仯����֪ͨ
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeActions
		*/
		virtual void TAP_CDECL OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info);
		/**
		* @brief ���ز�ѯ�ĳֲֻ���
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeInfo
		*/
		virtual void TAP_CDECL OnRspQryPositionSummary(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIPositionSummary *info);

		/**
		* @brief �ֲֻ��ܱ仯����֪ͨ
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeActions
		*/
		virtual void TAP_CDECL OnRtnPositionSummary(const TapAPIPositionSummary *info);
		/**
		* @brief �ֲ�ӯ��֪ͨ
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeActions
		*/
		virtual void TAP_CDECL OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info);


		/**
		* @brief ����ϵͳ�еı�����Ϣ
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_TradeSystem
		*/
		virtual void TAP_CDECL OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info);

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
		virtual void TAP_CDECL OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info);
		/**
		* @brief	������Ϣ֪ͨ
		* @details	�û��ڽ��׹����п�����Ϊ�ʽ𡢳ֲ֡�ƽ�ֵ�״̬�䶯ʹ�˻�����ĳЩΣ��״̬������ĳЩ��Ҫ����Ϣ��Ҫ���û�֪ͨ��
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_AccountDetails
		*/
		virtual void TAP_CDECL OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info);
		/**
		* @brief ��ʷί�в�ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info);
		/**
		* @brief ��ʷί�����̲�ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info);
		/**
		* @brief ��ʷ�ɽ���ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info);
		/**
		* @brief ��ʷ�ֲֲ�ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info);
		/**
		* @brief ��ʷ�����ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info);
		/**
		* @brief �ʽ������ѯӦ��
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] isLast 	��ʾ�Ƿ������һ������
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HisInfo
		*/
		virtual void TAP_CDECL OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info);
		/**
		* @brief ��ѯ�û��˵�Ӧ�� Add:2013.12.11
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_Bill
		*/
		virtual void TAP_CDECL OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info);
		/**
		* @brief ��ѯ�˻������Ѽ������ Add:2017.01.14
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_Rent
		*/
		virtual void TAP_CDECL OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info);
		/**
		* @brief ��ѯ�˻���֤�������� Add:2017.01.14
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_Rent
		*/
		virtual void TAP_CDECL OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info);

		/**
		* @brief �۽���������˫�߱���Ӧ�� Add:2017.08.29
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HKMarket
		*/
		virtual void TAP_CDECL OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info);

		/**
		* @brief �۽���������˫�߳���Ӧ�� Add:2017.08.29
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HKMarket
		*/
		virtual void TAP_CDECL OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info);

		/**
		* @brief �۽���ѯ��֪ͨ Add:2017.08.29
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_HKMarket
		*/
		virtual void TAP_CDECL OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info);


		/**
		* @brief ����ɾ��Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info);

		/**
		* @brief ����¼��Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info);

		/**
		* @brief �����޸�Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info);

		/**
		* @brief ����ת��Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info);

		/**
		* @brief �ɽ�¼��Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info);

		/**
		* @brief ����ɾ��Ӧ�� Add:2017.12.05
		* @param[in] sessionID ����ĻỰID��
		* @param[in] errorCode �����롣0 ��ʾ�ɹ���
		* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
		* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
		* @ingroup G_T_LocalAction
		*/
		virtual void TAP_CDECL OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info);




#pragma endregion

	private:
		// ���׽ӿ���
		ITapTradeAPI* m_pTradeApi;

		// ��������ַ
		std::string m_host;
		// �������˿ں�
		uint16_t	m_port;

		// ���׽ӿڳ�ʼ����Ϣ
		TapAPIApplicationInfo m_stAppInfo;
		// ��Ȩ��Ϣ
		TapAPITradeLoginAuth m_stLoginAuth;

	};
}
