#pragma once

#include <unordered_map>
#include "TradeGateway.h"
#include "DataType.h"

namespace QCTech
{
	class TradeEngine
	{
	public:
		TradeEngine();
		virtual ~TradeEngine();
		
		// ��ӽ�������
		void AddGateway(TradeGateway& gw);
		
		// ��ȡ��������
		TradeGateway* GetGateway(std::string gatewayName);

	public:
		// ����ȫ����������
		void Connect();
		// ���������ӽ�������
		void Connect(std::string gatewayName);

		void InsertOrder(StructInsertOrderReq& stOrder, std::string gatewayName);
	private:
		std::unordered_map<std::string, TradeGateway&> m_mapTradeGateway;
	};
}