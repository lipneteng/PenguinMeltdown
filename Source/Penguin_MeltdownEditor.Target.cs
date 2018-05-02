// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Penguin_MeltdownEditorTarget : TargetRules
{
	public Penguin_MeltdownEditorTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Editor;

        ExtraModuleNames.Add("Penguin_Meltdown");
    }

}
