-- menu.lua

-- create main menu
function n_CreateMainMenu()
	-- File
	PX2EU_MAN:Menu_Main_AddMainItem("File", (PX2_LM_EDITOR:V("n_File")))
	PX2EU_MAN:Menu_Main_AddItem("File", "NewProject", PX2_LM_EDITOR:V("n_NewProject").."\tCtrl-N", "n_NewProject", "Proj_NewProject")
	PX2EU_MAN:Menu_Main_AddItem("File", "Open", PX2_LM_EDITOR:V("n_Open").."\tCtrl-O", "n_OpenProject", "Proj_Open")
	PX2EU_MAN:Menu_Main_AddItem("File", "Save", PX2_LM_EDITOR:V("n_Save").."\tCtrl-S", "n_SaveProject", "Proj_Save")
	PX2EU_MAN:Menu_Main_AddItem("File", "Close", PX2_LM_EDITOR:V("n_Close"), "n_CloseProject", "Proj_Close")
	PX2EU_MAN:Menu_Main_AddItemSeparater("File")
	PX2EU_MAN:Menu_Main_AddItem("File", "NewScene", PX2_LM_EDITOR:V("n_NewScene").."\tCtrl-N", "n_NewScene", "Proj_Scene_NewScene")
	PX2EU_MAN:Menu_Main_AddItem("File", "Open", PX2_LM_EDITOR:V("n_Open"), "n_OpenScene", "Proj_Scene_Open")
	PX2EU_MAN:Menu_Main_AddItem("File", "Save", PX2_LM_EDITOR:V("n_Save"), "n_SaveScene", "Proj_Scene_Save")
	PX2EU_MAN:Menu_Main_AddItem("File", "SaveAs", PX2_LM_EDITOR:V("n_SaveAs"), "n_SaveSceneAs", "Proj_Scene_SaveAs")
	PX2EU_MAN:Menu_Main_AddItem("File", "Close", PX2_LM_EDITOR:V("n_Close"), "n_CloseScene", "Proj_Scene_Close")
	PX2EU_MAN:Menu_Main_AddItemSeparater("File")
	PX2EU_MAN:Menu_Main_AddItem("File", "Exit", PX2_LM_EDITOR:V("n_Exit"), "n_Exit", "")
	
	-- Edit
	PX2EU_MAN:Menu_Main_AddMainItem("Edit", (PX2_LM_EDITOR:V("n_Edit")))
	PX2EU_MAN:Menu_Main_AddItem("Edit", "UnDo", PX2_LM_EDITOR:V("n_UnDo").."\tCtrl-Z", "n_UnDo", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "ReDo", PX2_LM_EDITOR:V("n_ReDo").."\tCtrl-R", "n_ReDo", "")
	PX2EU_MAN:Menu_Main_AddItemSeparater("Edit")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Copy", PX2_LM_EDITOR:V("n_Copy").."\tCtrl-C", "n_Copy", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Paste", PX2_LM_EDITOR:V("n_Paste").."\tCtrl-V", "n_Paste", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Clone", PX2_LM_EDITOR:V("n_Clone").."\tCtrl-D", "n_Clone", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Delete", PX2_LM_EDITOR:V("n_Delete").."\tDelete", "n_DeleteSelection", "")
	PX2EU_MAN:Menu_Main_AddItemSeparater("Edit")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Import", PX2_LM_EDITOR:V("n_Import").."\tCtrl-I", "n_Import", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Export", PX2_LM_EDITOR:V("n_Export").."\tCtrl-E", "n_Export", "")
	PX2EU_MAN:Menu_Main_AddItemSeparater("Edit")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Select", PX2_LM_EDITOR:V("n_Select"), "", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Translate", PX2_LM_EDITOR:V("n_Translate"), "", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Rotate", PX2_LM_EDITOR:V("n_Rotate"), "", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Scale", PX2_LM_EDITOR:V("n_Scale"), "", "")
	PX2EU_MAN:Menu_Main_AddItemSeparater("Edit")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "PlayAndStop", PX2_LM_EDITOR:V("n_PlayAndStop"), "", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "ResetPlay", PX2_LM_EDITOR:V("n_ResetPlay"), "", "")
	
	-- View
	PX2EU_MAN:Menu_Main_AddMainItem("View", (PX2_LM_EDITOR:V("n_View")))
	PX2EU_MAN:Menu_Main_AddSubItem("View", "Window", (PX2_LM_EDITOR:V("n_Window")))
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "Project", (PX2_LM_EDITOR:V("n_Project")), "", "")
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "Stage", (PX2_LM_EDITOR:V("n_Stage")), "", "")
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "ResView", (PX2_LM_EDITOR:V("n_ResView")), "", "")
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "Inspector", (PX2_LM_EDITOR:V("n_Inspector")), "", "")
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "Console", (PX2_LM_EDITOR:V("n_Console")), "", "")
	PX2EU_MAN:Menu_Main_AddItem("ViewWindow", "PreView", (PX2_LM_EDITOR:V("n_PreView")), "", "")
	
	-- Debug
	PX2EU_MAN:Menu_Main_AddMainItem("Debug", (PX2_LM_EDITOR:V("n_Debug")))
	
	-- Tool
	PX2EU_MAN:Menu_Main_AddMainItem("Tool", (PX2_LM_EDITOR:V("n_Tool")))
	
	-- Help
	PX2EU_MAN:Menu_Main_AddMainItem("Help", (PX2_LM_EDITOR:V("n_Help")))
	PX2EU_MAN:Menu_Main_AddItem("Help", "About", (PX2_LM_EDITOR:V("n_About")), "", "")
end

function n_CreateMainMenu1()
	-- File
	PX2EU_MAN:Menu_Main_AddMainItem("File", (PX2_LM_EDITOR:V("n_File")))
	PX2EU_MAN:Menu_Main_AddItem("File", "NewFile", PX2_LM_EDITOR:V("n_NewFile").."\tCtrl-N", "n_NewFile", "Proj_NewFile")
	PX2EU_MAN:Menu_Main_AddItemSeparater("File")
	PX2EU_MAN:Menu_Main_AddItem("File", "OpenFile", PX2_LM_EDITOR:V("n_OpenFile").."\tCtrl-O", "n_NewFile", "Proj_OpenFile")
	PX2EU_MAN:Menu_Main_AddItem("File", "OpenDir", PX2_LM_EDITOR:V("n_OpenDir"), "n_OpenDir()", "Proj_OpenDir")
	PX2EU_MAN:Menu_Main_AddItemSeparater("File")
	PX2EU_MAN:Menu_Main_AddItem("File", "Save", PX2_LM_EDITOR:V("n_Save").."\tCtrl-S", "n_Save", "Proj_Save")
	PX2EU_MAN:Menu_Main_AddItem("File", "SaveAs", PX2_LM_EDITOR:V("n_SaveAs").."\tCtrl-Shift-S", "n_SaveSceneAs", "Proj_Scene_SaveAs")
	PX2EU_MAN:Menu_Main_AddItem("File", "SaveAll", PX2_LM_EDITOR:V("n_SaveAll"), "n_SaveAll", "Proj_SaveAll")
	PX2EU_MAN:Menu_Main_AddItemSeparater("File")
	PX2EU_MAN:Menu_Main_AddItem("File", "Exit", PX2_LM_EDITOR:V("n_Exit"), "n_Exit", "")
	
	-- Edit
	PX2EU_MAN:Menu_Main_AddMainItem("Edit", (PX2_LM_EDITOR:V("n_Edit")))
	PX2EU_MAN:Menu_Main_AddItem("Edit", "UnDo", PX2_LM_EDITOR:V("n_UnDo").."\tCtrl-Z", "n_UnDo", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "ReDo", PX2_LM_EDITOR:V("n_ReDo").."\tCtrl-R", "n_ReDo", "")
	PX2EU_MAN:Menu_Main_AddItemSeparater("Edit")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Copy", PX2_LM_EDITOR:V("n_Copy").."\tCtrl-C", "n_Copy", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Paste", PX2_LM_EDITOR:V("n_Paste").."\tCtrl-V", "n_Paste", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Clone", PX2_LM_EDITOR:V("n_Clone").."\tCtrl-D", "n_Clone", "")
	PX2EU_MAN:Menu_Main_AddItem("Edit", "Delete", PX2_LM_EDITOR:V("n_Delete").."\tCtrl-Delete", "n_DeleteSelection", "")
	
	-- Debug
	PX2EU_MAN:Menu_Main_AddMainItem("Debug", (PX2_LM_EDITOR:V("n_Debug")))
	
	-- Tool
	PX2EU_MAN:Menu_Main_AddMainItem("Tool", (PX2_LM_EDITOR:V("n_Tool")))
	
	-- Help
	PX2EU_MAN:Menu_Main_AddMainItem("Help", (PX2_LM_EDITOR:V("n_Help")))
	PX2EU_MAN:Menu_Main_AddItem("Help", "About", (PX2_LM_EDITOR:V("n_About")), "", "")
end