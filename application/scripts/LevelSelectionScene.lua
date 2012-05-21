LevelSelectionScene = {}

LevelSelectionScene.new = function() 
	
	local scene = Scene:newScene();
	scene:onEnter(function()
						Director:clearMemoryCache();
						-- Add bg
						local screenBg = Sprite:spriteWithFile("application/resources/images/app/levelselect-bg.png")
						screenBg.position = Screen:getCenterPoint();
						scene:addChild(screenBg)
						-- Add castle
						Sprite:loadSheet("application/resources/images/app/menuItemsSprites.plist", "application/resources/images/app/menuItemsSprites.png")
						local castle = Sprite:spriteWithFrame("Castle.png")		
						castle.position = Point(418 , 184)
						scene:addChild(castle);
						-- Add back button
						Sprite:loadSheet("application/resources/images/app/buttonSprites.plist")
						local btn = Button:buttonAtPoint({70, 27})
						btn:setImage(Sprite:spriteWithFrame("BtnBackNormal.png"),"normal")
						btn:onPress(function(event) event.item:runAction(Action:scaleTo(0.1,1.5)) end)
						btn:onRelease(function(event) 
											event.item:runAction(Action:scaleTo(0.1,1.0)) 
											Director:showScene(MenuScene:new(),"fadein", 0.5)
										end)
						scene:addChild(btn, 20);

						-- Add the level selection buttons
						local scroll = ScrollLayer:newLayer();
						local numberOfLevels = 30;
						local numberOfPages = (numberOfLevels / 12.0) + 1;
						local levelIndex = 0;
						local page = 0;
						local scrollPage = Layer:newLayer();
						scroll:addPage(scrollPage);
						for level = 1, numberOfLevels do
							-- Button bg
							local levelBtn = Button:buttonAtPoint(Point((levelIndex % 4) * 100 + 90, Screen:getSize().height - math.floor(levelIndex / 4.0) * 80 - 50))
							levelBtn:setImage(Sprite:spriteWithFile("application/resources/images/app/levelselect-level-button.png"),"normal")
							levelBtn:onPress(function(event) event.item:runAction(Action:scaleTo(0.1,1.5)) end)
							levelBtn:onCancel(function(event) event.item:runAction(Action:scaleTo(0.1,1.0)) end)
							levelBtn:onRelease(function(event) 
													event.item:runAction(Action:scaleTo(0.1,1.0)) 
												end)
							levelBtn.tag = level;
							scrollPage:addChild(levelBtn);	
							-- Level number
							local lblLvlNum = Label:newLabel(tostring(level), levelBtn.width / 2, levelBtn.height / 2 + 5, "application/resources/fonts/BerlinSansFB32.fnt");
							lblLvlNum.scale = 0.7;
							levelBtn:addChild(lblLvlNum);	
							-- Star
							for i = 1, 3 do
								local star = Sprite:spriteWithFile("application/resources/images/app/levelselect-star.png")
								star.scale = 0.4
								star.position = Point(7 + i * 9 ,16);
								levelBtn:addChild(star)
							end
														
							local lblLvlNum = Label:newLabel(tostring(level), levelBtn.width / 2, levelBtn.height / 2 + 5, "application/resources/fonts/BerlinSansFB32.fnt");
							lblLvlNum.scale = 0.7;
							levelBtn:addChild(lblLvlNum);	
							
							
							levelIndex=levelIndex+1;
							if (levelIndex == 12) then
								levelIndex = 0;
								page=page+1;
								scrollPage = Layer:newLayer();
								scroll:addPage(scrollPage);
							end			
						end
						scene:addChild(scroll,50)		
						Settings["test"] = "testing";
       					end)
	return scene
end