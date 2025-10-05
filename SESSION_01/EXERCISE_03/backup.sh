backup_root="/tmp/backup_exercise"
read -p "Insert path of folder to back up: " to_backup
backup_dir="backup_"$(date +%Y%m%d_%H%M%S)
mkdir -p $backup_root"/"$backup_dir
cp -a $to_backup $backup_root"/"$backup_dir
tar czf $backup_root"/"$backup_dir".tar.gz" $backup_root"/"$backup_dir 
