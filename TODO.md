# TODO
<br>

> <h3>Application</h3>
>> <h4>Component</h4>
>> &ensp;&ensp;&ensp;&ensp; ☑️ RenderTarget    
>> &ensp;&ensp;&ensp;&ensp; ☑️ Event                                            
>> &ensp;&ensp;&ensp;&ensp; ☑️ Input        
> 
> <h3>Entity component system</h3>
>> <h4>World query</h4>
>> &ensp;&ensp;&ensp;&ensp; ✅ Include component                                                                     
>> &ensp;&ensp;&ensp;&ensp; ✅ Exclude component                                                                     
>> &ensp;&ensp;&ensp;&ensp; ✅ Marker flag to not return component                                                   
>> &ensp;&ensp;&ensp;&ensp; ✅ Avoid type duplicate on both Include and Exclude                                      
>> &ensp;&ensp;&ensp;&ensp; ✅ Avoid type duplicate between Include and Exclude                                      
>> &ensp;&ensp;&ensp;&ensp; ✅ Only accept raw type on exclude (like no Marker\<T> or other)                         
>> &ensp;&ensp;&ensp;&ensp; ☑️ Handle unregistered component                                                         
>> &ensp;&ensp;&ensp;&ensp; ✅ Directly accept world query in system declaration                                     
>> &ensp;&ensp;&ensp;&ensp; ☑️ Add application component support like event, resources... based on registered plugin
>>
>> <h4>Entity</h4>
>> &ensp;&ensp;&ensp;&ensp; ✅️ Versioning                        
>> &ensp;&ensp;&ensp;&ensp; ✅️ Manage alive statement
>>
>> <h4>System</h4>
>> &ensp;&ensp;&ensp;&ensp; ✅️ Implement priority \
>> &ensp;&ensp;&ensp;&ensp; ✅️ Keep order ??                
>> &ensp;&ensp;&ensp;&ensp; ✅️ Refactor to allow user defined system                                 
>> &ensp;&ensp;&ensp;&ensp; ☑️ Startup system                                                           
>>
>> <h4>Bundle</h4>
>> &ensp;&ensp;&ensp;&ensp; ☑️ Interface with required and opt behaviours \
>> &ensp;&ensp;&ensp;&ensp; ☑️ Capacity to register application component 
>
> <h3>Graphics</h3>
>> <h4></h4>
>
> <h3>Physics</h3>
>> To be determined
> 
> <h3>Math</h3>
>> <h4>Vector</h4>
>> &ensp;&ensp;&ensp;&ensp; ☑️ Lerp
>> 
>> <h4>Matrix</h4>
>> &ensp;&ensp;&ensp;&ensp; ☑️ More than just 4x4 matrix
>> 
>> <h4>Other</h4>
>> &ensp;&ensp;&ensp;&ensp; ☑️ Quaternion \
>> &ensp;&ensp;&ensp;&ensp; ☑️ Frustum
