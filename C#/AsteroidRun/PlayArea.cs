using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// PlayArea is a simple component that describes the size of the play area - this governs invader movement etc.
public class PlayArea : MonoBehaviour
{
    // width and height of the play area (it is assumed the centre of the play area is at x = y = 0)
    [SerializeField] private float width = 0;
    [SerializeField] private float height = 0;

    // Accessor methods to return the width and height of the play area
    // Note: The above attributes have the [SerializeField] attribute so we can set them in Unity, but once set we cannot change them
    public float getWidth()
    {
        return width;
    }

    public float getHeight()
    {
        return height;
    }
}
