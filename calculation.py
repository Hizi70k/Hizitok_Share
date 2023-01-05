import numpy as np
import pandas as pd
from math import sqrt

start_date = 20210125
end_date = 20221130

excel_url = "E:\Personal\quant202301/1.xlsx"

df = pd.read_excel(excel_url,sheet_name="Sheet1",index_col=0)

# ret = retracement
noun_trans = {
    "复权单位净值":"value_",
    "指数":"index_",
    "产品日收益率":"day_rate",
    "指数日收益率":"day_rate_index",
    "产品回撤":"ret_value",
    "指数回撤":"ret_index",
    "是否回填最大回撤":"if_max_ret"
    }
df.rename(columns=noun_trans,inplace=True)

sdate = pd.to_datetime(start_date, format= "%Y%m%d").strftime("%Y-%m-%d")

edate = pd.to_datetime( end_date , format= "%Y%m%d").strftime("%Y-%m-%d")

#trading days 
trading_days = df[sdate:edate].shape[0] - 1

const_day = 245

edate_value = df.loc[edate,"value_"]

total_inc_value = df.loc[edate,"value_"] / df.loc[sdate,"value_"] -1

total_inc_index = df.loc[edate,"index_"] / df.loc[sdate,"index_"] -1

min_value = df["value_"].min()

min_value_date = df[ df["value_"] == min_value ].index

corr_index = df["value_"].corr( df["index_"] )

# Y = year, inc = increase, vol = volatility
Y_inc_val = ( 1+ total_inc_value )**( const_day / trading_days ) -1

Y_inc_index = ( 1+ total_inc_index )**( const_day / trading_days ) -1

Y_inc_extra = Y_inc_val - Y_inc_index

Y_vol_val = df["day_rate"].std()* sqrt( const_day )

Y_vol_index =  df["day_rate_index"].std()* sqrt( const_day )

Y_sharpe = Y_inc_val / Y_vol_val

ret_max = df["ret_value"].min()

ret_max_index = df["ret_index"].min()

ret_max_edate = df[ df["ret_value"] == ret_max ].index[0].strftime("%Y-%m-%d")

rmax_s = df[sdate:ret_max_edate]["value_"].max()

ret_max_sdate = df[ df["value_"] == rmax_s ].index[0].strftime("%Y-%m-%d")

print(ret_max_sdate)
print(ret_max_edate)

period_inc_index = df.loc[ret_max_sdate,"index_"] / df.loc[ret_max_edate,"index_"] -1

drawback = df[ df["value_"] == df[ret_max_edate:edate]["value_"].max() ]

ret_max_drawback = 0
if ( drawback.shape[0] > 0 ):
    ret_max_drawback = drawback.index[0].strftime("%Y-%m-%d")




out = pd.DataFrame( data = {"edate_value":edate_value,
                            "Y_avg_rate": Y_inc_val,
                            "Y_avg_index":Y_inc_index,
                            "extra_rate":Y_inc_extra,
                            "Y_volatility_rate":Y_vol_val,
                            "Y_volatility_index":Y_vol_index, 
                            "sharpe":Y_sharpe,

                            "max_ret": ret_max,
                            "period_inc_index":period_inc_index,
                            "maxRet_begin":ret_max_sdate,
                            "maxRet_end"  :ret_max_edate,
                            "maxRet_drawback":ret_max_drawback,

                            "total_inc_value":total_inc_value,
                            "total_inc_index":total_inc_index,

                            "total_min_value":min_value,
                            "min_value_date":min_value_date,
                            "corr":corr_index,
                            },index= [1]
                   )

print(out)


