# emergesync
Sync portage without spamming their servers.

```MIN_TIME``` reflects the minimum amount of time in seconds before allowing a sync.

```
emergesync  [  -f  -uc  -t  -ts  ]
-f    --force         =    Force syncing portage, updating the @world set, and depclean ask.
-uc   --updateclean   =    Skip syncing portage then update the @world set and depclean ask.
-t    --time          =    Get formatted time since last portage sync operation.
-ts   --timesec       =    Get raw seconds since last portage sync opeation.  
```
