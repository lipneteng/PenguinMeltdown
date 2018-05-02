// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Penguin_MeltdownTarget : TargetRules
{
    public Penguin_MeltdownTarget(TargetInfo Target) : base(Target)
    {
		Type = TargetType.Game;

        ExtraModuleNames.Add("Penguin_Meltdown");
	}
}
