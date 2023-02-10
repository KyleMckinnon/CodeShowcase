using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaterProperties : MonoBehaviour
{
   public Material Water;
   public float RippleSpeed;
   public float RippleDensity;
   public float RippleSlimness;
    public float WaveSpeed;
   public Color Ripplecolor;
   public Color Basecolor;
   public Renderer rend;

    //Added this script to be able to edit bodies of water at ease inside of unities inspector to make it easier for others to use

    // Start is called before the first frame update
    void Start()
    {
        Water.SetFloat("_RippleSpeeed", RippleSpeed);
        Water.SetFloat("_RippleDensity", RippleDensity);
        Water.SetFloat("_RippleSlimness", RippleSlimness);
        Water.SetFloat("_WaveSpeed", WaveSpeed);
        Water.SetColor("_RippleColor", Ripplecolor);
        Water.SetColor("_BaseColor", Basecolor);
    }

    // Update is called once per frame
    void Update()
    {
       rend.material.SetFloat("_RippleSpeeed", RippleSpeed);
       rend.material.SetFloat("_RippleDensity", RippleDensity);
       rend.material.SetFloat("_RippleSlimness", RippleSlimness);
        rend.material.SetFloat("_WaveSpeed", WaveSpeed);
        rend.material.SetColor("_RippleColor", Ripplecolor);
       rend.material.SetColor("_BaseColor", Basecolor);
    }
}
