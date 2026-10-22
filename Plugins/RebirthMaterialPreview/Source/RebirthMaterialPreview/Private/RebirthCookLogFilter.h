#pragma once

/**
 * Keeps commandlets (cook, Alpakit's PackagePlugin cook, resave) from failing on retail shader maps.
 *
 * Loading a retail cooked material (RM_Surface, the RMI_Surface_* family, every character material that uses them)
 * makes RenderCore compare the frozen shader map layout saved by Square Enix's build with this editor's layout. They
 * never match, so ShaderMap.cpp logs "LogShaders: Error: Mismatch size/hash for type ..." (14 lines per material) and
 * discards that shader map. Nothing is wrong with the content being cooked, but every commandlet counts those lines,
 * returns 1, and UAT stops with "Cook failed" (ExitCode 25).
 *
 * Install() wraps GWarn in commandlets only. Exactly those two LogShaders messages are logged at Display instead of
 * Error; every other message, error count and warning count passes through unchanged. Pass -RebirthKeepShaderMismatchErrors
 * on the command line to turn it off.
 */
namespace RebirthCookLogFilter
{
	void Install();
	void Uninstall();
}
