MenuScene = {}

MenuScene.new = function() 
	
	local scene = Scene:newScene();
	scene:onEnter(function()
                        
						-- Add bg
						local screenBg = Sprite:spriteWithFile("application/resources/images/app/menu-bg.jpg")
						screenBg.position = Screen:getCenterPoint();
						scene:addChild(screenBg)
						
						-- Add castle
						Sprite:loadSheet("application/resources/images/app/menuItemsSprites.plist", "application/resources/images/app/menuItemsSprites.png")
						local castle = Sprite:spriteWithFrame("Castle.png")		
						castle.position = Point(359.0 , 201.0)
						castle.scale = 0.7;
						scene:addChild(castle)
						
						-- Add the charactor
						Sprite:loadSheet("application/resources/images/app/menuSprites.plist")
						Sprite:loadSheet("application/resources/images/app/menuSprites1.plist")
						local charactor = Sprite:spriteWithFrame("char-wind-bchar-wind-blowing_00.png")
						charactor.position = Point(165.0, 143.0)
						scene:addChild(charactor)		
						
						local frames = Action:makeFrameSequence("char-wind-bchar-wind-blowing_%02d.png", 0, 13);
						charactor:runAction(Action:repeatAction(Action:animation(0.1,unpack(frames)),-1))
						-- Add front grass
						local frontGrass = Sprite:spriteWithFrame("front strands for animation_00.png")
						frontGrass.position = Point(145.0, 44.0)
						scene:addChild(frontGrass)		
						local frames = Action:makeFrameSequence("front strands for animation_%02d.png", 0, 35);
						frontGrass:runAction(Action:repeatAction(Action:animation(0.1,unpack(frames)),-1))
						-- Add back grass
						local backGrass = Sprite:spriteWithFrame("back strands for animation_00.png")
						backGrass.position = Point(145, 50)
						scene:addChild(backGrass,-1)		
						frames = Action:makeFrameSequence("back strands for animation_%02d.png", 0, 35);
						backGrass:runAction(Action:repeatAction(Action:animation(0.1,unpack(frames)),-1))
						
						Sprite:loadSheet("application/resources/images/app/buttonSprites.plist")
						local btn = Button:buttonAtPoint({70, 27})
						btn:setImage(Sprite:spriteWithFrame("BtnPlayNormal.png"),"normal")
						btn:onPress(function(event) event.item:runAction(Action:scaleTo(0.1,1.5)) end)
						btn:onRelease(function(event) 
											event.item:runAction(Action:scaleTo(0.1,1.0)) 
											Director:showScene(LevelSelectionScene:new(),"fadein", 0.5)
										end)
						scene:addChild(btn, 20);
						
						btn = Button:buttonAtPoint({290, 30})
						btn:setImage(Sprite:spriteWithFrame("BtnTwitterNormal.png"),"normal")
						btn:onPress(function(event) event.item:runAction(Action:scaleTo(0.1,1.5)) end)
						btn:onRelease(function(event) event.item:runAction(Action:scaleTo(0.1,1.0)) end)
						scene:addChild(btn, 20);
						
                        
						btn = Button:newButton({
                                            x=340, 
                                            y=30,
                                            normal=Sprite:spriteWithFrame("BtnFacebookNormal.png"),
                                            onPress=function(event) 
                                                        event.item:runAction(Action:scaleTo(0.1,1.5)) 
                                                    end,
                                            onRelease=function(event) 
                                                        event.item:runAction(Action:scaleTo(0.1,1.0))
                                                    end
                                            })
						--btn:setImage(,"normal")
						--btn:onPress(function(event) event.item:runAction(Action:scaleTo(0.1,1.5)); end)
						--btn:onRelease(function(event) event.item:runAction(Action:scaleTo(0.1,1.0)) end)
						scene:addChild(btn, 20);
       					end)
	return scene
end