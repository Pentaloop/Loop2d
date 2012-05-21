function Action.sequence(repeatCount, ...)
	--print("action.sequence() : END")
	assert(type(repeatCount) == "number", "Action.sequence(): 'repeatCount' not specified" );
	local arg = {...}
	assert(#arg > 0, "Action.sequence(): At least 1 action is needed for sequence");
	local actions = cocos2d.CCArray:array();
	for i,v in ipairs(arg) do
		--assert(v.repeatCount > 0, "Action.sequence(): Sequence cannot contain an action with infinit repeatCount (repetitions = 0)")
		--print(v.repeatCount)
		--table.insert(actionList, v)
		actions:addObject(v)
	end
	
	if actions:count() > 0 then
		print(actions:count())
		local sequenceAction = cocos2d.CCSequence:actionsWithArray(actions);
		-- Create the repeatition wrapper
		local anAction = sequenceAction
		if (repeatCount < 1) then
			anAction = cocos2d.CCRepeatForever:actionWithAction(anAction)
		elseif (repeatCount > 1) then
			anAction = cocos2d.CCRepeat:actionWithAction(anAction, repeatCount)
		end
		return anAction;		
	else
		print("Action.sequence(): count not create action list for sequence")
	end
	return nil;
end


function Action:animation(delay, ...)
	assert(type(delay) == "number", "Action.animation(): 'delay' not specified" );
	local arg = {...}
	assert(#arg > 0, "Action.animation(): At least 1 frame is needed for animation");
	return Action:frameAnimation(delay, #arg, arg);
	--[[
	local frames = cocos2d.CCArray:array();
	for i,v in ipairs(arg) do
	
	print("Action.animation() : START3")
		local frame = cocos2d.CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(v);
		frames:addObject(frame)
	end
	print("Action.animation() : START4")
	if frames:count() > 0 then
		--print("Action.animation() : Frames created")
		local animation = cocos2d.CCAnimation:animationWithFrames(frames, delay);
		if animation then
			print("Action.animation() : START5")
		end
		
		local animateAction = cocos2d.CCAnimate:actionWithAnimation(animation);
		if animateAction then
			print("Action.animation() : START6")
		end
		return animateAction;		
	else
		print("Action.animation(): count not create action list for frames")
	end
	return nil;
	]]--
end


function Action:makeFrameSequence(template, startFrame, endFrame, stride)
	if stride == nil then
		if startFrame < endFrame then
			stride = 1
		else 
			stride = -1
		end			
	end
	local frames = {};
	for frameNumber = startFrame, endFrame, stride do
		table.insert(frames, string.format(template, frameNumber))
	end
	return frames
end

