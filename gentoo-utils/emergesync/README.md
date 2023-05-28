# emergesync
Sync portage without spamming their servers.

```MIN_TIME``` reflects the minimum amount of time in seconds before allowing a sync.

```
emergesync  [  -h  -f  -uc  -t  -ts  ] [ -na ]


First argument
  -h    --help
  -f    --force         =    Force syncing portage, updating the @world set, and depclean ask.
  -uc   --updateclean   =    Skip syncing portage then update the @world set and depclean ask.
  -t    --time          =    Get formatted time since last portage sync operation.
  -ts   --timesec       =    Get raw seconds since last portage sync opeation.
  -s    --sync-only     =    Only sync repos.

Second argument
  -na   --no-ask        =    Don't ask before emerge. 
```
