-- language.lua

function l_AddLanguage()
	PX2_LM_APP:Clear()
	PX2_LM_APP:AddItem("Engine", "PHOENIXEngine", "PHOENIXEngine")
	PX2_LM_APP:AddItem("01Robot", "零一机器人", "ZERONERobot")
	PX2_LM_APP:AddItem1("CodePlay", "编程玩")
	PX2_LM_APP:AddItem1("SignIn","登录")
	PX2_LM_APP:AddItem1("Launch", "启动")
	PX2_LM_APP:AddItem1("Open", "打开")
	PX2_LM_APP:AddItem1("Package", "打包")
	PX2_LM_APP:AddItem1("Editor", "编辑器")
	PX2_LM_APP:AddItem1("GenProjInfo", "生成项目信息")
	PX2_LM_APP:AddItem1("CreateNewProject","创建")
	PX2_LM_APP:AddItem1("FileProject","打开")
	PX2_LM_APP:AddItem1("GenPackage", "生成打包项目")
	PX2_LM_APP:AddItem1("Syn", "同步")
	PX2_LM_APP:AddItem1("SynAll", "同步所有")
	PX2_LM_APP:AddItem1("LoadProject", "加载项目")
	PX2_LM_APP:AddItem1("CloseProject", "关闭项目")
	PX2_LM_APP:AddItem1("Refresh", "刷新")
	PX2_LM_APP:AddItem1("Send", "发送")
	PX2_LM_APP:AddItem1("use the Facebook Signin","使用FaceBook登入")
	PX2_LM_APP:AddItem1("use the GooGle Signin","使用GooGle登入")
	PX2_LM_APP:AddItem("RememberMe", "记住我", "Remember me")
	PX2_LM_APP:AddItem1("Forget the passWord","忘记密码？")
	PX2_LM_APP:AddItem1("register","还没有账户，注册 或 稍后登入")
	PX2_LM_APP:AddItem1("Create new project","创建新项目")
	PX2_LM_APP:AddItem1("OK","确定")
	PX2_LM_APP:AddItem1("Cancel","取消")
	PX2_LM_APP:AddItem1("Login","登入")
	PX2_LM_APP:AddItem1("YouCreate", "天天块乐")
	PX2_LM_APP:AddItem("Testing","内测版", "Test")
	PX2_LM_APP:AddItem1("The Project Created can not be empty","创建的项目不能为空")
	PX2_LM_APP:AddItem1("Updating", "更新中")
	PX2_LM_APP:AddItem("GetFromTaobao", "从商店获得", "get from shop TaoBao")
	PX2_LM_APP:AddItem("Intell-Toy", "智能玩具", "Intell-Toy")
	PX2_LM_APP:AddItem("Chinese", "中文", "中文")
	PX2_LM_APP:AddItem("English", "English", "English")
	PX2_LM_APP:AddItem1("Cloud", "Cloud")
	PX2_LM_APP:AddItem1("Regist", "注册")
	PX2_LM_APP:AddItem1("Login", "登录")
	PX2_LM_APP:AddItem1("ForgetPassword","忘记密码")
	PX2_LM_APP:AddItem1("Account", "账号")
	PX2_LM_APP:AddItem1("Password", "密码")
	PX2_LM_APP:AddItem1("LoginOut", "登出")
	PX2_LM_APP:AddItem1("Projects", "项目  <项目已经可以在零一机器人云端分享>")
	PX2_LM_APP:AddItem1("Project", "项目")
	PX2_LM_APP:AddItem1("NetSyn", "网络同步  <通过Wifi局域网传输项目到设备, 进行远程更新>")
	PX2_LM_APP:AddItem1("Plugins", "插件")
	PX2_LM_APP:AddItem("ManyKit", "许多米科技", "MANYKIT")
end