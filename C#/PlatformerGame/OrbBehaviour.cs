using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OrbBehaviour : MonoBehaviour
{
    
   
    void OnTriggerEnter(Collider other)
    {
        GameController._instance.CollectedOrb();
        Destroy(this.gameObject);
        GameController._instance.playCollectSound();
    }


    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
