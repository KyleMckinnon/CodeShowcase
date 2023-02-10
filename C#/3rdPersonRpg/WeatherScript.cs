using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeatherScript : MonoBehaviour
{

    public GameObject[] WeatherParticles;
    private int randomParticle;

    private float rainChance = 0.5f;
    //private float rainLength;

    private float dice;

    private bool isSnowing;

    private float timer = 0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(!isSnowing)
        {
            dice = Random.Range(0f, 100f);
            if(dice < rainChance)
            {
                randomParticle = Random.Range(0, WeatherParticles.Length);
                Snow(randomParticle);
                isSnowing = true;
                timer = Random.Range(5f, 20f);
            }
        }

        if(isSnowing)
        {
            timer -= Time.deltaTime;
            if(timer <= 0 )
            {
                isSnowing = false;
                StopSnow(randomParticle);
            }
        }
    }

    private void Snow(int randomParticle)
    {
        WeatherParticles[randomParticle].SetActive(true);
    }

    private void StopSnow(int randomParticle)
    {
        WeatherParticles[randomParticle].SetActive(false);
    }
}
