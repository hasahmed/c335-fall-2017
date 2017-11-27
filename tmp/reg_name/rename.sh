for file in reg_names*
do
    mv -i "${file}" "${file/reg_names/reg_name}"
done
