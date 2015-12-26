#pragma once

#include <map>
#include <typeinfo>
#include "../interfaces/TAssetHandler.h"

namespace ae
{
	class AssetManager
	{
	private:
		std::map<const std::string, IAssetHandler*> m_Handlers;
	public:
		AssetManager() {}
		~AssetManager() {}

		template<class TYPE>
		TAssetHandler<TYPE>& GetHandler() const {

		}

		IAssetHandler& GetHandler(const std::string id) const {
			return
		}
		void RegisterHandler(IAssetHandler* handler);
		bool LoadAllAssets(void);
	};
}