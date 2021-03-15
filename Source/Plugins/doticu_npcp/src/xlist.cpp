/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

namespace doticu_npcp { namespace XList {

    // certain xdata cannot be moved to another container without creating issues, e.g. worn, leveleditem. Others are just unneeded.
    u64 Clean_For_Move(XList_t *xlist, TESObjectREFR *ref_to) {
        if (!xlist || !Object_Ref::Get_XContainer(ref_to, false)) {
            return 0;
        }
        
        s64 count_xdatas = 0;
        std::vector<XData_t *> vec_xdatas_to_destroy;
        for (XData_t *xdata = xlist->m_data; xdata != NULL; xdata = xdata->next) {
            u64 type = xdata->GetType();

            if (type == kExtraData_Ownership) {
                ExtraOwnership *xownership = (ExtraOwnership *)xdata;
                if (!xownership->owner) {
                    vec_xdatas_to_destroy.push_back(xdata);
                }
            } else if (type == kExtraData_Worn ||
                       type == kExtraData_WornLeft ||
                       type == kExtraData_OutfitItem ||
                       type == kExtraData_LeveledItem ||
                       type == kExtraData_CannotWear ||
                       type == kExtraData_ShouldWear) {
                vec_xdatas_to_destroy.push_back(xdata);
            }

            count_xdatas += 1;
        }

        for (u64 idx = 0, size = vec_xdatas_to_destroy.size(); idx < size; idx += 1) {
            XData_t *xdata = vec_xdatas_to_destroy[idx];
            xlist->Remove(xdata->GetType(), xdata);
            XData::Destroy(xdata);
        }

        return count_xdatas - vec_xdatas_to_destroy.size();
    }

}}
