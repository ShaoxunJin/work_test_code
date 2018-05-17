#include "stdafx.h"

#include "WH.h"

static int iCount;
static int iCountFor = 10;

struct_contain_struct::struct_contain_struct() : a(10)
{

}

ostream& operator<<(ostream& os, WH4A_LOC_ENUM loc)
{
	os<<WHenum2str(loc);
	return os;
}

WH::WH_VECTOR_PAIR_UI_UI wh_memory_section = WH::WH_VECTOR_PAIR_UI_UI();


WH::WH(int i_nbr, WH4A_LOC_ENUM from, WH4A_LOC_ENUM to)
: m_nbr(i_nbr)
, m_from(from)
, m_to(to)
{
	//cout<<__FUNCTION__<<">"<<endl;
	function_in
	
	vec_bool.push_back(SMEE_FALSE);
	vec_bool.push_back(SMEE_FALSE);
	vec_bool.push_back(SMEE_FALSE);
	vec_bool.push_back(SMEE_TRUE);
	vec_bool.push_back(SMEE_FALSE);
	//m_matrix[WH4A_LOC_MAX][WH4A_LOC_MAX] = {1};
	reset_m_matrix();

	function_out
}

WH::WH(int i_nbr)
:m_nbr(i_nbr)
{

}

WH::WH(char* name)
:pBuffer(name)
{
	cout<<"name = "<<name<<endl;
}

WH::WH()
{
	cout<<"construct without parameter !"<<endl;
	pBuffer = new char[256];
	//memset((void *)pBuffer, '\0', sizeof(pBuffer));
	//cout<<"buffer = "<<pBuffer<<endl;
};

WH::~WH()
{
	cout<<__FUNCTION__"<"<<endl;
}

void WH::reset_m_matrix()
{
	memset(m_matrix, 0x0, sizeof(m_matrix));

	m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_PREALIGNER] = SMEE_TRUE;
	//干涉，等待机械
	m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_DISCHARGE] = SMEE_FALSE;
	m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_WAFER_STAGE_CHUCK1] = SMEE_TRUE;
	m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_WAFER_STAGE_CHUCK2] = SMEE_TRUE;

	//测试过程 直接更改机械手和片库之间的配置关系
	m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_PORT] = SMEE_FALSE;
	m_matrix[WH4A_LOC_PORT][WH4A_LOC_LOAD_ROBOT] = SMEE_FALSE;
	m_matrix[WH4A_LOC_PORT][WH4A_LOC_UNLOAD_ROBOT] = SMEE_FALSE;

	//干涉，等待机械
	m_matrix[WH4A_LOC_UNLOAD_ROBOT][WH4A_LOC_PREALIGNER] = SMEE_FALSE;
	m_matrix[WH4A_LOC_UNLOAD_ROBOT][WH4A_LOC_DISCHARGE] = SMEE_TRUE;
	m_matrix[WH4A_LOC_UNLOAD_ROBOT][WH4A_LOC_PORT] = SMEE_FALSE;

	m_matrix[WH4A_LOC_PREALIGNER][WH4A_LOC_LOAD_ROBOT] = SMEE_TRUE;
	//干涉，等待机械
	m_matrix[WH4A_LOC_PREALIGNER][WH4A_LOC_UNLOAD_ROBOT] = SMEE_FALSE;
	//干涉，等待机械
	m_matrix[WH4A_LOC_DISCHARGE][WH4A_LOC_LOAD_ROBOT] = SMEE_FALSE;
	m_matrix[WH4A_LOC_DISCHARGE][WH4A_LOC_UNLOAD_ROBOT] = SMEE_TRUE;

	m_matrix[WH4A_LOC_WAFER_STAGE_CHUCK1][WH4A_LOC_UNLOAD_ROBOT] = SMEE_TRUE;
	m_matrix[WH4A_LOC_WAFER_STAGE_CHUCK2][WH4A_LOC_UNLOAD_ROBOT] = SMEE_TRUE;

	if(SMEE_TRUE)
	{
		m_matrix[WH4A_LOC_DISCHARGE][WH4A_LOC_TRACK] = SMEE_TRUE;
		m_matrix[WH4A_LOC_TRACK][WH4A_LOC_PREALIGNER] = SMEE_TRUE;
	}
	/*WHSPDM_CARRIER_CONFIG_ENUM carrier_config = s_config.carrier_config();
	if(carrier_config == WHSPDM_CI_CARRIER_AT_LEFT ||
		carrier_config == WHSPDM_CI_CARRIER_AT_RIGHT)
	{
		if(s_spdm.get_equipment(
			WH4A_LOC_PORT).get_carrier_state() == WH4A_CARRIER_MAPPED)
		{
			if(carrier_config == WHSPDM_CI_CARRIER_AT_LEFT)
			{
				m_matrix[WH4A_LOC_LOAD_ROBOT][WH4A_LOC_PORT] = SMEE_TRUE;
			}
			else
			{
				m_matrix[WH4A_LOC_UNLOAD_ROBOT][WH4A_LOC_PORT] = SMEE_TRUE;
			}
			if(carrier_config == WHSPDM_CI_CARRIER_AT_LEFT)
			{
				m_matrix[WH4A_LOC_PORT][WH4A_LOC_LOAD_ROBOT] = SMEE_TRUE;
			}
			else
			{
				m_matrix[WH4A_LOC_PORT][WH4A_LOC_UNLOAD_ROBOT] = SMEE_TRUE;
			}
		}
	}*/
}

SMEE_BOOL WH::result()
{
	cout<<__FUNCTION__<<">"<<endl;
	SMEE_BOOL bLikned = SMEE_TRUE;
	for (vector< boost::shared_ptr<WH> >::iterator iter = m_link.begin();
		iter != m_link.end() && bLikned;
		++iter)
	{
		if(!(*iter)->result());
		cout<<"!(*iter)->result() = "<<!(*iter)->result()<<endl;
	}
	cout<<__FUNCTION__<<"<"<<endl;

	return bLikned;
}

void WH::add_link(boost::shared_ptr<WH> ptr)
{
	cout<<__FUNCTION__<<">"<<endl;

	cout<<__FUNCTION__<<"<"<<endl;
}

SMEE_BOOL WH::out_put_type(boost::any &para)
{
	//return typeid(int) == para.type();
	//cout<<"boost::any &para = "<<para.type().name()<<endl;
	cout<<""<<boost::any_cast<int>(&para)<<endl;
	return 1;
}

void WH::getNbr(int *number)
{
	*number = m_nbr;
}

int WH::operator+(int nbr)
{
	return this->m_nbr + nbr;
}

int WH::operator*(int nbr)
{
	return (this->m_nbr + nbr)*10;
}

boost::shared_ptr<WH> WH::function_return_wh()
{
	return shared_from_this();
}

void WH::optimise_route(WH4A_LOC_ENUM from, WH4A_LOC_ENUM to)
{
	function_in
	m_cancel_buff_pos_as_route(from, to);
	ROUTE_LOC route_loc;
	m_optimise_route(from, to, route_loc);
	int i = 0;

	if (route_loc.empty())
	{
		cout<<"No Route !"<<endl;
	}

	for (ROUTE_LOC::iterator iter = route_loc.begin();
		iter != route_loc.end();
		++iter)
	{
		cout<<"result["<<i<<"] = "<<*iter<<endl;
	}
	function_out
}

void WH::m_optimise_route(WH4A_LOC_ENUM from,
						  WH4A_LOC_ENUM to,
						  ROUTE_LOC& route_loc)
{
	function_in
	cout<<from<<"---->>>>"<<to<<endl;
	SMEE_BOOL searched[WH4A_LOC_MAX];
	ROUTE_LOC dfs_route;
	memset(searched, 0x0, sizeof(searched));

	//深度优先搜索
	dfs_route.push_back(from);

#if 1
	for (ROUTE_LOC::iterator iter = dfs_route.begin();
		iter != dfs_route.end();
		++iter)
	{
		cout<<"dfs_route = "<<*iter<<endl;
	}
	
	for (ROUTE_LOC::iterator iter = route_loc.begin();
		iter != route_loc.end();
		++iter)
	{
		cout<<"route_loc = "<<*iter<<endl;
	}

#endif
	//if(to == WH4A_LOC_PORT && target_slot != WHAPRC_MOVE_PROCESS_PARAMETER::ANY_SLOT)
	//{
	//	ostringstream os;
	//	if(WHSPFC::check_slot_occupy(target_slot, os))
	//	{
	//		WRH_TRACE(os.str());
	//		return SMEE_FALSE;
	//	}
	//}
	//else if(to == WH4A_LOC_PORT && target_slot == WHAPRC_MOVE_PROCESS_PARAMETER::ANY_SLOT)
	//{
	//	if(WH4A_MAX_SLOT_NBR == WHSPDM::instance().get_substrate_c().get_empty_slot())
	//	{
	//		WRH_TRACE("no empty slot");
	//		return SMEE_FALSE;
	//	}
	//}

	//if(from == to && from != WH4A_LOC_PORT)
	//{
	//	route_loc.push_back(from);
	//}
	//else
	//{
		m_dfs(from, to, searched, dfs_route, route_loc);
	//}

	cout<<"route_loc.empty() = "<<route_loc.empty()<<endl;
	function_out
}

void WH::m_dfs(WH4A_LOC_ENUM loc,
		   WH4A_LOC_ENUM target,
		   SMEE_BOOL searched[WH4A_LOC_MAX],
		   ROUTE_LOC& dfs_route,//已经找到的路径
		   ROUTE_LOC& optimize_route)
{
	function_in
	int i = 0;

#ifdef _WH_DEBUG_INFO_
	for (ROUTE_LOC::iterator iter = dfs_route.begin();
		iter != dfs_route.end();
		++iter,++i)
	{
		cout<<"dfs_route["<<i<<"]="<<*iter<<endl;
	}
	i = 0;
	for (ROUTE_LOC::iterator iter = optimize_route.begin();
		iter != optimize_route.end();
		++iter,++i)
	{
		cout<<"optimize_route["<<i<<"]="<<*iter<<endl;
	}
#endif

	ROUTE_LOC::iterator optimize_loc_it;
	for(WH4A_LOC_ENUM next_loc = WH4A_LOC_MIN; next_loc < WH4A_LOC_MAX; ++reinterpret_cast<int&>(next_loc))
	{
		//如果loc到next loc的路径存在 并且 next loc没有被处理过
		if(m_matrix[loc][next_loc] && !searched[next_loc])
		{
			if(next_loc == target)
			{
				if(dfs_route.size() < optimize_route.size() || optimize_route.empty())
				{
					optimize_route = (ROUTE_LOC(dfs_route.begin(),dfs_route.end()));
					optimize_route.push_back(target);

					#ifdef _WH_DEBUG_INFO_
					int i = 0;
					for (ROUTE_LOC::iterator iter = optimize_route.begin();
						iter != optimize_route.end();
						++iter, ++i)
					{
						cout<<"optimize_route["<<i<<"] = "<<*iter<<endl;
					}
					#endif

					break;//如果搜索到了下一个目标位置 则可以跳出搜索
				}
			}
			searched[next_loc] = SMEE_TRUE;
			dfs_route.push_back(next_loc);
			#ifdef _WH_DEBUG_INFO_
			int i = 0;
			for (ROUTE_LOC::iterator iter = dfs_route.begin();
				iter != dfs_route.end();
				++iter, ++i)
			{
				cout<<"dfs_route["<<i<<"] = "<<*iter<<endl;
			}
			#endif
			//递归搜索next loc ->next next loc
			//20161105 这里的目的就是先找到一个 然后根据现在整个找到的重新找下一个
			m_dfs(next_loc, target, searched, dfs_route, optimize_route);
		}
		// 现在路径为 n...loc,寻找next loc,如最优路径为p...loc...next loc
		// 当n->next_loc < p->next_loc时，则n->next_loc为最优路径
		else if(m_matrix[loc][next_loc] && !optimize_route.empty())
		{
			optimize_loc_it = find(
				optimize_route.begin(), optimize_route.end(),next_loc);
			if(optimize_loc_it != optimize_route.end())
			{
				if(static_cast<int>(dfs_route.size()) < (optimize_loc_it - optimize_route.begin()))
				{         
					optimize_route.erase(optimize_route.begin(), optimize_loc_it);
					optimize_route.insert(optimize_route.begin(), dfs_route.begin(), dfs_route.end());
				}
			}
		}
	}
	//上次搜索没有结果，退栈
	dfs_route.pop_back();
	function_out
	for (ROUTE_LOC::iterator iter = dfs_route.begin();
		iter != dfs_route.end();
		++iter)
	{
		cout<<*iter<<endl;
	}
}

void WH::m_cancel_buff_pos_as_route( WH4A_LOC_ENUM from, WH4A_LOC_ENUM to )
{
	function_in
	//暂时不支持port作为中间缓存空间进行move
	if(from != WH4A_LOC_PORT && to != WH4A_LOC_PORT)
	{
		for(int loc_loop = WH4A_LOC_MIN; loc_loop != WH4A_LOC_MAX; ++loc_loop)
		{
			m_matrix[WH4A_LOC_PORT][loc_loop] = 0;
			m_matrix[loc_loop][WH4A_LOC_PORT] = 0;
		}
	}
	//不支持将工件台作为中间缓存空间进行move
	if(from != WH4A_LOC_WAFER_STAGE_CHUCK1 && to != WH4A_LOC_WAFER_STAGE_CHUCK1)
	{
		for(int loc_loop = WH4A_LOC_MIN; loc_loop != WH4A_LOC_MAX; ++loc_loop)
		{
			m_matrix[WH4A_LOC_WAFER_STAGE_CHUCK1][loc_loop] = 0;
			m_matrix[loc_loop][WH4A_LOC_WAFER_STAGE_CHUCK1] = 0;
		}
	}
	//不支持将工件台作为中间缓存空间进行move
	if(from != WH4A_LOC_WAFER_STAGE_CHUCK2 && to != WH4A_LOC_WAFER_STAGE_CHUCK2)
	{
		for(int loc_loop = WH4A_LOC_MIN; loc_loop != WH4A_LOC_MAX; ++loc_loop)
		{
			m_matrix[WH4A_LOC_WAFER_STAGE_CHUCK2][loc_loop] = 0;
			m_matrix[loc_loop][WH4A_LOC_WAFER_STAGE_CHUCK2] = 0;
		}
	}
	//防止自动生成的路径利用track进行倒片...
	if(from != WH4A_LOC_TRACK)
	{
		m_matrix[WH4A_LOC_TRACK][WH4A_LOC_PREALIGNER] = SMEE_FALSE;
	}
	if(to != WH4A_LOC_TRACK)
	{
		m_matrix[WH4A_LOC_DISCHARGE][WH4A_LOC_TRACK] = SMEE_FALSE;
	}
	function_out
}

WH4A_LOC_ENUM WH::from()
{
	return this->m_from;
}

WH4A_LOC_ENUM WH::to()
{
	return this->m_to;
}

void WH::digui_function(int input)
{
	function_in;
	cout<<"input = " <<input<<endl;
	//for (int i = 0; i < input; ++i)
	//{
	//	cout<<"i = "<<i<<endl;
	//	/*if (i == input + 2)
	//	{
	//		cout<<"i = "<<i<<endl;
	//		if (i == input + 2)
	//		{
	//			break;
	//		}*/
	//	if (i == input -1)
	//	{
	//		if(i == 1)
	//		{
	//			break;
	//		}
	//		digui_function(input - 1);
	//	}
	//	//}	
	//}
	//for (int i = 0; i < input; ++i)
	for (int i = 1; i <= input; ++i)
	{
		cout<<"m_recursion("<<i<<") = "<<m_recursion(i)<<endl;
	}
	
	function_out;
}

//递归的思路：
//化繁为简 从最上层开始直接分解到最下层
//从最高层开始分解到最下层
int WH::m_recursion(int input)
{
#if 0
	if(0 == input || 1 == input)
	{
		return 1;
	}
	else
	{
		return m_recursion(input - 1) + m_recursion(input - 2);
	}
#endif

	if(1 == input)
	{
		return 1;
	}
	if (2 == input)
	{
		return 2;
	}
	else
	{
		return input * m_recursion(input - 1);
	}
};

//strcpy函数编写 目的也是测试返回值是char*类型
//返回char*的目的是可以进行 
char* WH::tt_strcpy(char* Dest, const char* Src)
{
	function_in;
	assert(NULL != Dest && NULL != Src);
	
	char* temp = Dest;
	cout<<"Dest = 0x"<<hex<<(void*)Dest<<endl;
	cout<<"Src = 0x"<<hex<<(void*)Src<<endl;
	//while ( (*Dest++ = *Src++) != '\0')
	while ( (*Dest = *Src) != '\0')//先取值 然后是赋值  然后是++
	{
		//cout<<"Dest = 0x"<<hex<<(void*)Dest<<endl;
		//cout<<"Src = 0x"<<hex<<(void*)Src<<endl;
		//cout<<"*Dest = "<<*Dest<<endl;
		//cout<<"*Src = "<<*Src<<endl;
		++Dest;
		++Src;
	}

	function_out;
	return temp;
}

void WH::add_attch_link(WH_PTR wh_ptr)
{
	function_in;
	m_attached_link.push_back(wh_ptr);
	cout<<"WH_PTR->m_nbr : "<<wh_ptr->m_nbr<<endl;
	function_out;
}

SMEE_BOOL WH::motion_is_finished()
{
	function_in;

	SMEE_BOOL finished = SMEE_TRUE;
	if(!m_motion_finished)
	{
		finished = SMEE_FALSE;
	}
	for(list<WH_PTR>::iterator it = m_attached_link.begin();
		it != m_attached_link.end() && finished; ++it)
	{
		finished = (*it)->motion_is_finished();
	}

	function_out;
	return finished;
}

SMEE_BOOL WH::motion_result()
{
	function_in;
	cout<<"iCount = "<<iCount++<<endl;
	
	SMEE_BOOL finished = SMEE_TRUE;
	for (std::list<WH_PTR>::iterator it = m_attached_link.begin();
		it != m_attached_link.end() && finished;
		++it)
	{
		static int iCountFor = 0;
		cout<<"iCountFor = "<<++iCountFor<<endl;
		cout<<"(*it)->m_nbr = "<<(*it)->m_nbr<<endl;
		finished = (*it)->motion_result();
		cout<<"finished = "<<finished<<endl;
	}
	function_out;

	return finished;
}

WH& WH::operator=(const WH& rhs)
{
	//如果是自我拷贝 则立马返回
	if (this == &rhs)
	{
		return *this;
	}
	//这里只针对动态内存进行拷贝；
	int iLength = strlen(rhs.pBuffer);
	cout<<"iLength = "<<iLength<<endl;
	delete []pBuffer;
	pBuffer = new char[iLength + 1];
	memcpy((void *)pBuffer, (void *)rhs.pBuffer, sizeof(iLength + 1));
	
	for (int i = 0; i < iLength + 1; ++i)
	{
		cout<<pBuffer[i]<<endl;
		cout<<rhs.pBuffer[i]<<endl;
	}
	return *this;
}

string& any_test_1(int para)
{
	return string("jinshao");
}
ProductA::ProductA()
{
	cout<<__FUNCTION__<<endl;
}
ProductA::~ProductA()
{
	cout<<__FUNCTION__<<endl;
}
void ProductA::do_something()
{
	cout<<__FUNCTION__<<endl;
}

ProductB::ProductB()
{
	cout<<__FUNCTION__<<endl;
}
ProductB::~ProductB()
{
	cout<<__FUNCTION__<<endl;
}
void ProductB::do_something()
{
	cout<<__FUNCTION__<<endl;
}

void factor_function_test()
{
	cout<<">>>"<<__FUNCTION__<<endl;

	//工厂对象 产生一个工厂  模板类实例化
	ObjectFactory<std::string, Product> productFactory;
	//注册产品 注册对象构造器
	productFactory.RegisterObjectCreator("A", boost::factory<ProductA*>());
	productFactory.RegisterObjectCreator("B", boost::factory<ProductB*>());
	
	//这里是采用基类指针指向派生类对象
	ptrProduct ProductA(productFactory.makeObject("A"));
	ptrProduct ProductB(productFactory.makeObject("B"));

	//多态性质
	ProductA->do_something();
	ProductB->do_something();

	cout<<"<<<"<<__FUNCTION__<<endl;
}


Manager::Manager()
{
	function_in;
}

void Manager::registerCallBack(boost::function<void (int)> f)
{
	function_in;
	this->fds.push_back(f);
	function_out;
}

//这个i就是用来返回当前vector中的位置
void Manager::runCallBack(int i)
{
	function_in;
	cout<<">>>>>>>>running method in Node, other class !"<<endl;
	//for (int i = 0; i < this->fds.size(); ++i)
	//{
		boost::function<void (int)> ptrFun = this->fds[i];
		ptrFun(i);
	//}

	function_out;
}

void Manager::subscribe_runCallBack(boost::function<void (int)> f, int i)
{
	function_in;
	f(i);
	function_out;
}

void Manager::fcn(int i)
{
	cout<<__FUNCTION__<<" ; "<<i<<endl;
}

Node::Node()
{
	function_in;
}

Node::Node(Manager *managerPtr)
{
	this->pManager = managerPtr;
}

void Node::A(int i)
{
	cout<<"A : "<<i<<endl;
}

void Node::B(int i)
{
	cout<<"B : "<<i<<endl;
}

void Node::C(int i)
{
	cout<<"C : "<<i<<endl;
}

void Node::start()
{
	//函数注册的参数采用占位符来实现
	function_in;
	this->pManager->registerCallBack(boost::BOOST_BIND(&Node::A, shared_from_this(), _1));
	this->pManager->registerCallBack(boost::BOOST_BIND(&Node::B, shared_from_this(), _1));
	this->pManager->registerCallBack(boost::BOOST_BIND(&Node::C, shared_from_this(), _1));

	function_out;
}

Obj::Obj(Manager * pManager)
{
	this->managerPtr = pManager;
}

void Obj::fun_1(int i)
{
	cout<<__FUNCTION__<<" : "<<i<<endl;
}

void Obj::fun_2(int i)
{
	cout<<__FUNCTION__<<" : "<<i<<endl;
}

void Obj::start()
{
	this->managerPtr->registerCallBack(boost::BOOST_BIND(&Obj::fun_1, shared_from_this(),_1));
	this->managerPtr->registerCallBack(boost::BOOST_BIND(&Obj::fun_2, shared_from_this(),_1));
}

void test_callback()
{
	function_in;

	Manager* pManager = new Manager();
	boost::shared_ptr<Node> nodePtr(new Node(pManager));
	boost::shared_ptr<Obj> objPtr(new Obj(pManager));
	nodePtr->start();
	objPtr->start();
	
	pManager->runCallBack(0);

	cout<<"Begin to bind test............................"<<endl;
	//boost::function<void (int)> fff;
	//fff = boost::BOOST_BIND(&Manager::runCallBack, pManager, _1);
	//fff(4);
	//下面的"_1"就是runCallBack中的输入参数
	pManager->subscribe_runCallBack(boost::BOOST_BIND(&Manager::runCallBack, pManager, _1),4);
	cout<<"Finish to bind test...."<<endl;

	myCallBackFun(myFun2, 0);

	delete pManager;
	pManager = NULL;
	function_out;
}

void myFun1(int i)
{
	cout<<__FUNCTION__<<" : "<<i<<endl;
}
void myFun2(int i)
{
	cout<<__FUNCTION__<<" : "<<i<<endl;
}
void myFun3(int i)
{
	cout<<__FUNCTION__<<" : "<<i<<endl;
}


void myCallBackFun(ptrFun fp, int i)
{
	function_in;

	function_out;
	//fp(i);
}

const char * WHenum2str(const WH4A_LOC_ENUM& t)
{
	const char *str;
	switch(t)
	{
	case WH4A_LOC_MIN:
		str = "LOC_MIN";
		break;
	case WH4A_LOC_PORT:
		str = "LOC_PORT";
		break;
	case WH4A_LOC_LOAD_ROBOT:
		str = "LOC_LOAD_ROBOT";
		break;
	case WH4A_LOC_UNLOAD_ROBOT:
		str = "LOC_UNLOAD_ROBOT";
		break;
	case WH4A_LOC_PREALIGNER:
		str = "LOC_PREALIGNER";
		break;
	case WH4A_LOC_DISCHARGE:
		str = "LOC_DISCHARGE";
		break;
	case WH4A_LOC_WAFER_STAGE_CHUCK1:
		str = "LOC_WAFER_STAGE_CHUCK1";
		break;
	case WH4A_LOC_WAFER_STAGE_CHUCK2:
		str = "LOC_WAFER_STAGE_CHUCK2";
		break;
	case WH4A_LOC_TRACK:
		str = "LOC_TRACK";
		break;
	case WH4A_LOC_MAX:
		str = "LOC_MAX";
		break;
	default:
		str = "INVALID WH4A_LOC_ENUM Value";
		break;
	}
	return str;
}


void tt_digui_for()
{
	function_in;
	cout<<"iCountFor = "<<iCountFor<<endl;
	for (; iCountFor > 0; )
	{
		cout<<"iCountFor = "<<iCountFor--<<endl;
		tt_digui_for();
	}

	function_out;
}

void tt_digui_result()
{
	function_in;

	WH tt;
	boost::shared_ptr<WH> link_1(new WH(1));
	boost::shared_ptr<WH> link_2(new WH(2));
	boost::shared_ptr<WH> link_3(new WH(3));
	tt.add_attch_link(link_1);
	tt.add_attch_link(link_2);
	tt.add_attch_link(link_3);

	cout<<"size = "<<tt.m_attached_link.size()<<endl;
	tt.motion_result();

	function_out;
}

OPERATOR_EQUAL_CLASS::OPERATOR_EQUAL_CLASS( int iNbr )
:iSize(iNbr)
{
	cout<<"Construct...iNbr = "<<iNbr<<endl;
	pBUFFER = new char[iSize];
}

OPERATOR_EQUAL_CLASS::~OPERATOR_EQUAL_CLASS()
{
	cout<<"Destrcut ...."<<endl;
	delete [] pBUFFER;
}

//OPERATOR_EQUAL_CLASS& OPERATOR_EQUAL_CLASS::operator =(const OPERATOR_EQUAL_CLASS &rhs)
//{
//	if (this == &rhs)
//	{
//		return *this;
//	}
//	delete [] pBUFFER;
//	pBUFFER = new char[rhs.iSize];
//	memcpy(pBUFFER, rhs.pBUFFER, rhs.iSize);
//	return *this;
//}

ConcreteOBSERVE_1::ConcreteOBSERVE_1(SUBJECT* pSubject)
: m_pSubjec_1(pSubject)
{

}

ConcreteOBSERVE_1::~ConcreteOBSERVE_1()
{

};

void ConcreteOBSERVE_1::update(int new_value)
{
	cout<<__FUNCTION__<<" new state = "<<new_value<<endl;
	
}

ConcreteOBSERVE_2::ConcreteOBSERVE_2(SUBJECT* pSubject)
:m_pSubject_2(pSubject)
{

}

ConcreteOBSERVE_2::~ConcreteOBSERVE_2()
{

}

void ConcreteOBSERVE_2::update(int new_value)
{
	cout<<__FUNCTION__<<" new state = "<<new_value<<endl;
}

ConcreteSUBJECT::ConcreteSUBJECT(int state)
:m_state(state)
{
	cout<<"subject cosntruction state = "<<state<<endl;
}

ConcreteSUBJECT::~ConcreteSUBJECT()
{

}

void ConcreteSUBJECT::registerSubject(OBSERVE *pObserve)
{
	m_ObserveList.push_back(pObserve);
	cout<<"registerSubject successs !"<<endl;
}

void ConcreteSUBJECT::removeSubject(OBSERVE* pObserve)
{
	m_ObserveList.remove(pObserve);
	cout<<"removeSubject successs !"<<endl;
}

void ConcreteSUBJECT::notify()
{
	list<OBSERVE*>::iterator iter = m_ObserveList.begin();
	while (m_ObserveList.end() != iter)
	{
		(*iter)->update(m_state);
		++iter;
	}
}

void ConcreteSUBJECT::setState(int state)
{
	m_state = state;
	cout<<__FUNCTION__<<state<<endl;
}

int& ConcreteSUBJECT::getState()
{
	return m_state;
}

void test_subject_observe()
{
	function_in;
	
	//创建一个subject
	ConcreteSUBJECT* subject = new ConcreteSUBJECT(123);
	ConcreteOBSERVE_1* observe_1 = new ConcreteOBSERVE_1(subject);
	ConcreteOBSERVE_2* observe_2 = new ConcreteOBSERVE_2(subject);

	subject->registerSubject(observe_1);
	subject->registerSubject(observe_2);

	subject->setState(111);
	subject->notify();

	subject->removeSubject(observe_2);
	subject->setState(555);
	subject->notify();

	if (NULL != subject)
	{
		delete subject;
		subject = NULL;
	}
	if (NULL != observe_1)
	{
		delete observe_1;
		observe_1 = NULL;
	}
	if (NULL != observe_2)
	{
		delete observe_2;
		observe_2 = NULL;
	}
	function_out;
}