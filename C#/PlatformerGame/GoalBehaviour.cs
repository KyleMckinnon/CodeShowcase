using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GoalBehaviour : MonoBehaviour
{
    public string SceneName;
    ParticleSystem ps;
    // Start is called before the first frame update
    void Start()
    {
        ps = GetComponent<ParticleSystem>();
      
    }

    private void OnTriggerEnter(Collider other)
    {
        if(ps.isPlaying)
        {
            SceneManager.LoadScene(SceneName);
            print("You Win!!!");
           
        }
    }
}
