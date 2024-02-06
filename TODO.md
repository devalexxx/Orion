# TODO

Orion TODO list.

### Todo

> ☑️ ECS
>> ☑️ Delta time on update ?
> 
>> ☑️ Application component
>>> ☑️ RenderTarget (in bundle) \
    ☑️ Event \
    ☑️ Input (event related)
> 
>> ☑️ World query
>>> ✅ Include component \
    ✅ Exclude component \
    ✅ Marker flag to not return component \
    ✅ Avoid type duplicate on both Include and Exclude \
    ✅ Avoid type duplicate between Include and Exclude \
    ✅ Only accept raw type on exclude (like no Marker\<T> or other) \
    ☑️ Handle unregistered component \
    ✅ Directly accept world query in system declaration \
    ☑️ Add application component support like event, resources... based on registered plugin 
> 
>> ✅️ Entity
>>> ✅️ Versioning \
    ✅️ Manage alive statement 
>
>> ✅️ System
>>> ✅️ Implement priority \
    ✅️ Keep order ?? \
    ✅️ Refactor to allow user defined system
> 
>> ☑️ Bundle
>>> ☑️ Create the foundation
