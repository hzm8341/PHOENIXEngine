#ifndef EASYPRMANAGER_HPP
#define EASYPRMANAGER_HPP

#include "PX2Singleton_NeedNew.hpp"
#include "ProjectPre.hpp"

namespace PX2
{

	class EasyPRManager : public Singleton<EasyPRManager>
	{
	public:
		EasyPRManager();
		virtual ~EasyPRManager();

		bool Initlize();
		bool Ternimate();
	};

}

#endif