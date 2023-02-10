using UnityEditor;
using UnityEngine;

public class Tint
{
    private static string TintString(Color col)
    {
        return $"Tint; {col.r};{col.g};{col.b};{col.a}";

    }

    [InitializeOnEnterPlayMode]
    static void OnEnterPlaymodeEditor(EnterPlayModeOptions options)
    {
        if (options.HasFlag(EnterPlayModeOptions.DisableDomainReload))
        {
            EditorPrefs.SetString("Playmode tint", TintString(Color.black));

        }
        else
        {
            EditorPrefs.SetString("Playmode tint", TintString(Color.magenta));
        }
    }
}